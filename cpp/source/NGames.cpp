#include "../header/NGames.h"
#include <thread>
#include <chrono>
#include <functional>

NGames::NGames(int _num_of_games, Deck _deck, int _num_of_threads) : num_of_games(_num_of_games), deck(_deck), num_of_threads(_num_of_threads) {
    
}

void NGames::playOneGame() {
    game.initialize(deck);
    game.play();
}

void NGames::playGamesInBatch(){
    std::vector<std::thread> threads;
    
    for(int i = 0; i < num_of_threads; i++) {
        std::function<void()> func = [this] () {
            playOneGameAndFeedStat();
        };
        std::thread t(func);
        threads.push_back(std::move(t));
    }
    for(int i = 0; i < num_of_threads; i++){
        threads.at(i).join();
    }
}

void NGames::playRemainingGames(int remainder) {
    for(int i = 0; i < remainder; i++)
        playOneGameAndFeedStat();
}

void NGames::playGamesWithThreads() {
    int batch_number = num_of_games / num_of_threads;
    int remainder = num_of_games % num_of_threads;
    
    for(int i = 0; i < batch_number; i++) {
        playGamesInBatch();
    }

    if(remainder != 0)
        playRemainingGames(remainder);
    
}

void NGames::playOneGameAndFeedStat() {
    playOneGame();
    stat.feed(game.num_of_turns, deck);
}

void NGames::playGamesWithoutThreads() {
    for(int i = 0; i < num_of_games; i++){
        playOneGameAndFeedStat();
    }
}

void NGames::playGames() {

    auto start_time = std::chrono::system_clock::now().time_since_epoch();

    num_of_threads == 1 ? playGamesWithoutThreads() : playGamesWithThreads();

    auto end_time = std::chrono::system_clock::now().time_since_epoch();

    stat.setCompTime(std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count(), "micros");
}
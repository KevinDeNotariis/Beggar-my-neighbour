#include "../header/NGames.h"
#include <thread>
#include <chrono>
#include <functional>

NGames::NGames() {
    num_of_threads = 1;
    num_of_games = 1;
}

void NGames::initialize(int _num_of_games, Deck _deck, int _num_of_threads) {
    num_of_games = _num_of_games;
    deck = _deck;
    num_of_threads = _num_of_threads;

    if (num_of_threads > 1) {
        initializeDecksAndGamesForThreading();
    }
}

// -------------- NO THREADS METHODS --------------------
/*  NO THR  */ 
/*  NO THR  */ void NGames::playOneGame() {
/*  NO THR  */     game.initialize(deck);
/*  NO THR  */     game.play();
/*  NO THR  */ }
/*  NO THR  */ 
/*  NO THR  */ void NGames::playGamesWithoutThreads() {
/*  NO THR  */     for(int i = 0; i < num_of_games; i++){
/*  NO THR  */         playOneGameAndFeedStat();
/*  NO THR  */     }
/*  NO THR  */ }
/*  NO THR  */ 
/*  NO THR  */ void NGames::playOneGameAndFeedStat() {
/*  NO THR  */     playOneGame();
/*  NO THR  */     stat.feed(game.num_of_turns, deck.cards);
/*  NO THR  */ }
/*  NO THR  */ 
// -------------------------------------------------------

// ------------- THREADS METHODS -------------------------

void NGames::playOneGame(int i) {
    thread_games.at(i).initialize(thread_decks.at(i));
    thread_games.at(i).play();
}

std::vector<std::thread> NGames::generateThreadsAndPlayGames() {
    std::vector<std::thread> threads;

    for (int i = 0; i < num_of_threads; i++) {
        std::function<void()> func = [this, i]() {
            playOneGame(i);
        };
        std::thread t(func);
        threads.push_back(std::move(t));
    }
    return threads;
}

void NGames::joinThreads(std::vector<std::thread> &threads) {
    for (int i = 0; i < num_of_threads; i++)
        threads.at(i).join();
}

void NGames::playGamesInBatch(){

    std::vector<std::thread> threads = generateThreadsAndPlayGames();
    
    joinThreads(threads);

    feedStatsAfterThreading();
}


void NGames::feedStatsAfterThreading() {
    for (int i = 0; i < num_of_threads; i++)
        stat.feed(thread_games.at(i).num_of_turns, thread_decks.at(i).cards);
}

void NGames::initializeDecksAndGamesForThreading() {
    for (int i = 0; i < num_of_threads; i++) {
        thread_decks.push_back(deck);
        thread_games.push_back(Game());
    }
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

void NGames::playRemainingGames(int remainder) {
    for(int i = 0; i < remainder; i++)
        playOneGameAndFeedStat();
}

// --------------------------------------------------------


void NGames::playGames() {

    auto start_time = std::chrono::system_clock::now().time_since_epoch();

    num_of_threads == 1 ? playGamesWithoutThreads() : playGamesWithThreads();

    auto end_time = std::chrono::system_clock::now().time_since_epoch();

    stat.setCompTime(std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count(), "micros");
}
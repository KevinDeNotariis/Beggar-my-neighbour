#include "Game.h"
#include "Stat.h"

#include <thread>
#include <vector>

class NGames {
public:
    Deck deck;
    Game game;
    int num_of_games;

    //threads variables
    int num_of_threads;
    std::vector<Game> thread_games;
    std::vector<Deck> thread_decks;
    
    //statistics
    Stat stat;

    NGames(int, Deck, int _num_of_threads = 1);

    //Non-threading methods
    void playOneGame();
    void playGamesWithoutThreads();
    void playOneGameAndFeedStat();

    //Threading methods 
    void initializeDecksAndGamesForThreading();
    void playOneGame(int i);
    void playGamesInBatch();
    std::vector<std::thread> generateThreadsAndPlayGames();
    void joinThreads(std::vector<std::thread> &threads);
    void feedStatsAfterThreading();
    void playGamesWithThreads();
    void playRemainingGames(int);

    //Let's play the game!
    void playGames();
};
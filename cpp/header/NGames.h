#include "Game.h"
#include "Stat.h"

class NGames {
public:
    Deck deck;
    Game game;
    int num_of_games;
    int num_of_threads;
    
    Stat stat;

    NGames(int, Deck, int _num_of_threads = 1);

    void playOneGame();
    void playGamesWithThreads();
    void playGamesWithoutThreads();
    void playOneGameAndFeedStat();
    void playGamesInBatch();
    void playRemainingGames(int);
    void playGames();
};
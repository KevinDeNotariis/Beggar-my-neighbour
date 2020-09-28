#include <map>
#include "Game.h"

class NGames {
public:
    Deck deck;
    Game game;
    int num_of_games;
    std::map<int, int> stat;

    NGames(int, Deck);

    void playOneGame();
    void playGames();

    void feedStats();
};
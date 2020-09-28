#include "../header/NGames.h"

NGames::NGames(int _num_of_games, Deck _deck) : num_of_games(_num_of_games), deck(_deck) {}

void NGames::playOneGame() {
    game.initialize(deck);
    game.play();
}

void NGames::playGames() {
    for(int i = 0; i < num_of_games; i++){
        playOneGame();
        feedStats();
    }
}

void::NGames::feedStats() {}
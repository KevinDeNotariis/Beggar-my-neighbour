#pragma once
#include "Player.h"
#include "Deck.h"

class Game {

    void assignCards(Deck);
    void changeTurn();

public: 
    Player player1;
    Player player2;
    Player* active_player;
    std::vector<Card> table;

    Game();

    void initialize(Deck);
    
    void player1PlaysOneCard();
    void player2PlaysOneCard();
    
    void activePlayerPlaysOneCard();
};
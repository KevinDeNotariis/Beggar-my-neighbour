#pragma once
#include "Player.h"
#include "Deck.h"

class Game {

    void assignCards(Deck);
    void changeTurn();
    bool cardPlayedIsPenaltyCard(Card);
    bool activePlayerHasLost();

public: 
    Player player1;
    Player player2;
    Player* active_player;
    Player* non_active_player;
    std::vector<Card> table;
    int penalty_to_pay;
    bool end_game;
    int num_of_turns;

    Game();

    void initialize(Deck);

    void player1PlaysOneCard();
    void player2PlaysOneCard();
    
    void activePlayerPlaysOneCard();
    void activePlayerPlays();

    void takeProfit();

    void print();

    void play();
};
#pragma once

#include "Player.h"
#include "Deck.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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

    void initialize(Deck&);
    
    void activePlayerPlaysOneCard();
    void activePlayerPlays();

    void takeProfit();

    void print();

    void play();
};
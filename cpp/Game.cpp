#include "Game.h"
#include <iostream>

void Game::assignCards(Deck deck) {
    player1.cards = std::vector<Card>(deck.cards.begin(), deck.cards.begin()+20);
    player2.cards = std::vector<Card>(deck.cards.rbegin(), deck.cards.rbegin()+20);
}

void Game::changeTurn() {
    if(*active_player == player1){
        active_player = &player2;
        non_active_player = &player1;
    }else{
        active_player = &player1;
        non_active_player = &player2;
    }

    //active_player = *active_player == player1 ? &player2 : &player1;
}

Game::Game () {
}

void Game::initialize(Deck deck) {
    deck.shuffle();
    assignCards(deck);
    table.resize(0);
    penalty_to_pay = 0;
    end_game = false;

    active_player = &player1;
    non_active_player = &player2;
}

void Game::player1PlaysOneCard() {
    table.push_back(player1.playTop());
}

void Game::player2PlaysOneCard() {
    table.push_back(player2.playTop());
}

void Game::activePlayerPlaysOneCard() {
    table.push_back(active_player->playTop());
}

bool Game::cardPlayedIsPenaltyCard(Card card_played) {
    return (card_played.value == 1 || card_played.value == 2 || card_played.value == 3);
}

bool Game::activePlayerHasLost() {
    return active_player->cards.size() == 0;
}

void Game::activePlayerPlays() {
    do{
        activePlayerPlaysOneCard();

        if(cardPlayedIsPenaltyCard(table.back())){
            penalty_to_pay = table.back().value;
            break;
        }
        
        if(activePlayerHasLost()) {
            end_game = true;
            break;
        }

        penalty_to_pay--;

        if(penalty_to_pay == 0)
            takeProfit();

    }while(penalty_to_pay > 0);
    
    changeTurn();
}

void Game::takeProfit() {
    non_active_player->putUnder(table, "reversed");
    table.resize(0);
}
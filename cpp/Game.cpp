#include "Game.h"
#include <iostream>

void Game::assignCards(Deck deck) {
    player1.cards = std::vector<Card>(deck.cards.begin(), deck.cards.begin()+20);
    player2.cards = std::vector<Card>(deck.cards.rbegin(), deck.cards.rbegin()+20);
}

void Game::changeTurn() {
    active_player = *active_player == player1 ? &player2 : &player1;
}

Game::Game () {
}

void Game::initialize(Deck deck) {
    deck.shuffle();
    assignCards(deck);
    active_player = &player1;
}

void Game::player1PlaysOneCard() {
    table.push_back(player1.playTop());
}

void Game::player2PlaysOneCard() {
    table.push_back(player2.playTop());
}

void Game::activePlayerPlaysOneCard() {
    table.push_back(active_player->playTop());
    changeTurn();
}
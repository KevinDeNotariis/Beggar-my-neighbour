#pragma once
#include "Card.h"

#include <vector>


class Player {
public:
	std::vector<Card> cards;

	void initialize(std::vector<Card> starting_cards);

	// playTop means play the cards at the back of cards
	Card playTop();

	// putUnder means put at the beginning of cards.
	void putUnder(Card card_to_put_under);

	// putUnder with 'ordered' means the following:
	// if cards_to_put_under = {(1, coins), (2, swords)} and
	// this->cards = {(3, clubs)} then we get:
	// this->cards = {(1, coins), (2, swords), (3, clubs)}
	// while if we provide 'reversed' we get:
	// this-> = {(2, swords), (1, coins), (3, clubs)}
	void putUnder(std::vector<Card> cards_to_put_under, std::string order = "ordered");

	bool operator==(const Player&) const;
	bool operator==(Player&) const;

	void printCards();
};

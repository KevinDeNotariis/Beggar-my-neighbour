#pragma once
#include "Card.h"

#include <vector>


class Player {
public:
	std::vector<Card> cards;

	Player();

	void initialize(std::vector<Card> starting_cards);

	Card playTop();
	void putUnder(Card card_to_put_under);
	void putUnder(std::vector<Card> cards_to_put_under, std::string order = "ordered");
};

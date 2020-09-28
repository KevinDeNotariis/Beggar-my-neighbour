#pragma once

#include <vector>
#include <string>
#include "Card.h"

class Deck {
public:
	std::vector<Card> cards;
	unsigned seed;

	Deck();

	void initialize();

	bool isEmpty() const;
	bool contains(Card card) const;
	int size() const;
	Card popLast();
	void shuffle();
	void print();
};
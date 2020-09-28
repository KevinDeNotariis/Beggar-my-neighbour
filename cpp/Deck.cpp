#include "Deck.h"
#include <algorithm>
#include <chrono>
#include <random>

Deck::Deck() {
	initialize();
}

void Deck::initialize() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	cards.resize(0);
	std::vector<std::string> suits{ "clubs", "swords", "coins", "cups" };
	for (std::string suit : suits)
		for (int i = 1; i < 11; i++)
			cards.push_back(Card(i, suit));
}

bool Deck::isEmpty() const {
	return cards.size() == 0 ? true : false;
}
bool Deck::contains(Card card) const {
	return (std::find(cards.begin(), cards.end(), card) != cards.end());
}
int Deck::size() const {
	return cards.size();
}
Card Deck::popLast() {
	if (cards.size() != 0) {
		Card card = cards.back();
		cards.pop_back();
		return card;
	}
	else
		throw std::string("Deck has no more cards");
}

void Deck::shuffle() {
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}
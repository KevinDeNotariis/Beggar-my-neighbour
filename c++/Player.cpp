#include "Player.h"

Player::Player() {
}

void Player::initialize(std::vector<Card> starting_cards) {
	cards = starting_cards;
}

Card Player::playTop() {
	Card card = cards.back();
	cards.pop_back();
	return card;
}
void Player::putUnder(Card card_to_put_under) {
	cards.insert(cards.begin(), card_to_put_under);
}
void Player::putUnder(std::vector<Card> cards_to_put_under, std::string order) {
	if (order == "ordered")
		cards.insert(cards.begin(), cards_to_put_under.begin(), cards_to_put_under.end());
	else if (order == "reversed")
		cards.insert(cards.begin(), cards_to_put_under.rbegin(), cards_to_put_under.rend());
}

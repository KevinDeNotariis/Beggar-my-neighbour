#include "Card.h"
#include <iostream>

Card::Card(const Card& card) {
	this->value = card.value;
	this->suit = card.suit;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
	os << "(" << card.value << ", " << card.suit << ")";
	return os;
}

bool Card::operator==(const Card& card) {
	return (this->value == card.value && this->suit == card.suit);
}

bool Card::operator==(const Card& card) const{
	return (this->value == card.value && this->suit == card.suit);
}
#include "../header/Card.h"
#include <iostream>

Card::Card(const Card& card) {
	this->value = card.value;
	this->suit = card.suit;
}

std::string Card::toString() {
	std::string ret = "(" + std::to_string(value) + ", " + suit + ")";
	return ret;
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
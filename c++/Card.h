#pragma once

#include <string>
#include <ostream>

class Card
{
public:
	int value;
	std::string suit;

	Card() : value(0), suit("") {}
	Card(int _value, std::string _suit) : value(_value), suit(_suit) {}
	Card(const Card& card);

	friend std::ostream& operator<<(std::ostream& os, const Card& card);
	bool operator==(const Card& card);
	bool operator==(const Card& card) const;
};


#pragma once

#include <string>
#include <ostream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>

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

	friend class boost::serialization::access;
    
    template <class Archive> void serialize(Archive & ar, const unsigned int version){
		ar & value;
		ar & suit;
	}
};


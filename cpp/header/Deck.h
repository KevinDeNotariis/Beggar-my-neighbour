#pragma once

#include <vector>
#include <string>
#include "Card.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

	friend class boost::serialization::access;
    
    template <class Archive> void serialize(Archive & ar, const unsigned int version){
		ar & cards;
	}
};
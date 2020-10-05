#pragma once

#include <vector>
#include <iostream>
#include <ostream>
#include <string>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>

#include "Card.h"

class Stat {
    
protected:
    const std::string fillAsterisk(int length);
    const std::string spacesBetweenAsterisk(int length);
    const std::string printBoxedTitle(int length);
    const std::string wrapMessage(std::string message, int length);
public:

    // games.at(num_of_turns) = [ cards1, cards2, ....]
    std::vector<std::vector<std::vector<Card>>> games;
    int num_of_max_turns;

    std::vector<std::pair<int, int>> frequences;

    Stat();

    void feed(int, std::vector<Card>);
    void fillFrequences();
    unsigned long int numberOfGames();
    std::pair<int, std::vector<std::vector<Card>>> longestGame();
    std::vector<std::pair<int, std::vector<std::vector<Card>>>> gamesLongerThan(int);

    virtual std::string toString() = 0;
    std::string longestGameToString();
    std::string displayTable();
    void printTable(std::ostream&);

    void reset();

    friend class boost::serialization::access;

    template <class Archive> void serialize(Archive & ar, const unsigned int version){
        ar & games;
        ar & num_of_max_turns;
    }
};
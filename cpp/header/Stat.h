#include <vector>
#include <iostream>
#include <ostream>
#include <string>

#include "Card.h"

class Stat {
    
    std::pair<unsigned long long int, std::string>  computation_time;

    const std::string fillAsterisk(int length);
    const std::string spacesBetweenAsterisk(int length);
    const std::string printBoxedTitle(int length);
    const std::string wrapMessage(std::string message, int length);
public:

    std::vector<std::vector<std::vector<Card>>> games;

    std::vector<std::pair<int, int>> frequences;

    Stat();

    void feed(int, std::vector<Card>);
    void fillFrequences();
    unsigned long int numberOfGames();

    void setCompTime(unsigned long long int, std::string);
    unsigned long long int getCompTime();

    friend void operator<<(std::ostream&, Stat);
};
#include <vector>

#include "Deck.h"

class Stat {
    
    std::pair<unsigned long long int, std::string> computation_time;

public:

    std::vector<std::vector<Deck>> games;

    std::vector<std::pair<int, int>> frequences;

    Stat();

    void feed(int, Deck);
    void fillFrequences();

    void setCompTime(unsigned long long int, std::string);
    unsigned long long int getCompTime();
};
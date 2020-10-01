#include "../header/Stat.h"

Stat::Stat() {
    games.resize(10000);
    for(auto v : games)
        v.resize(0);
}

void Stat::feed(int num_of_games, Deck deck) {
    games.at(num_of_games).push_back(deck);
}

void Stat::fillFrequences() {
    for(int i = 0; i < games.size(); i++){
        if(games.at(i).size() != 0) {
            frequences.push_back(std::pair(i, games.at(i).size()));
        }
    }
}

void Stat::setCompTime(unsigned long long int time, std::string unit) {
    computation_time = std::pair(time, unit);
}

unsigned long long int Stat::getCompTime() {
    return computation_time.first;
}
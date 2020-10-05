#include "../header/GlobalStat.h"
#include "../header/Card.h"

#include <exception>


void GlobalStat::feed(LocalStat stat){
    try{
        for(int i = 0; i <= stat.num_of_max_turns; i++) {
            if(stat.games.at(i).size() != 0){
                for(auto cards : stat.games.at(i)){
                    this->games.at(i).push_back(cards);
                }
            }
                //this->games.at(i).insert(games.at(i).end(), stat.games.at(i).begin(), stat.games.at(i).end());
        }
        if(stat.num_of_max_turns > this->num_of_max_turns)
            this->num_of_max_turns = stat.num_of_max_turns;
    } catch (std::exception& e) {
        std::cout << "EXCEPTION: " << e.what() << std::endl;
    }
}

std::string GlobalStat::toString() {
    int length = 70;
    std::string ret = "";

    ret += printBoxedTitle(length);
    
    ret += wrapMessage("number of games played: " + std::to_string(numberOfGames()), length);
    ret += spacesBetweenAsterisk(length);

    ret += wrapMessage("longest game(s) was composed of " + std::to_string(num_of_max_turns) + " turns", length);
    ret += spacesBetweenAsterisk(length);

    ret += fillAsterisk(length);

    return ret;
}
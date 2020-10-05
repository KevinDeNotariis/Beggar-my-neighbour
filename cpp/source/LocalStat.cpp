#include "../header/LocalStat.h"

void LocalStat::setCompTime(unsigned long long int time, std::string unit) {
    computation_time = std::pair(time, unit);
}

unsigned long long int LocalStat::getCompTime() {
    return computation_time.first;
}

std::string LocalStat::toString() {
    int length = 40;
    std::string ret = "";

    ret += printBoxedTitle(length);

    ret += wrapMessage("computation time: " + std::to_string(getCompTime()) + " " + computation_time.second, length);
    ret += spacesBetweenAsterisk(length);
    ret += wrapMessage("number of games played: " + std::to_string(numberOfGames()), length);
    ret += spacesBetweenAsterisk(length);
    ret += fillAsterisk(length);

    return ret;
}
#include "../header/Stat.h"

#include <string>

Stat::Stat() {
    games.resize(10000);
    for(auto v : games)
        v.resize(0);
}

void Stat::feed(int num_of_games, std::vector<Card> cards) {
    games.at(num_of_games).push_back(cards);
}

void Stat::fillFrequences() {
    for(int i = 0; i < games.size(); i++){
        if(games.at(i).size() != 0) {
            frequences.push_back(std::pair(i, games.at(i).size()));
        }
    }
}

unsigned long int Stat::numberOfGames() {
    unsigned long int number_of_games = 0;
    for (int i = 0; i < games.size(); i++)
        if(games.at(i).size() != 0)
            number_of_games+=games.at(i).size();

    return number_of_games;
}

void Stat::setCompTime(unsigned long long int time, std::string unit) {
    computation_time = std::pair(time, unit);
}

unsigned long long int Stat::getCompTime() {
    return computation_time.first;
}

void operator<<(std::ostream& os, Stat stat) {
    int length = 40;

    os << stat.printBoxedTitle(length);

    os << stat.wrapMessage("computation time: " + std::to_string(stat.getCompTime()) + " " + stat.computation_time.second, length);
    os << stat.spacesBetweenAsterisk(length);
    os << stat.wrapMessage("number of games played: " + std::to_string(stat.numberOfGames()), length);
    os << stat.spacesBetweenAsterisk(length);
    os << stat.fillAsterisk(length);
}

const std::string Stat::wrapMessage(std::string message, int length) {
	std::string out = "";

	out += "*";
	for (int i = 0; i < ((length-1) - message.length()) / 2; i++)
		out += " ";

	out += message;

	while (out.length() < (length-1))
		out += " ";

	out += "*\n";

	return out;
}

const std::string Stat::fillAsterisk(int length) {
    std::string ret = "";
    for(int i = 0; i < length; i++)
        ret += "*";

    ret += "\n";
    return ret;
}

const std::string Stat::spacesBetweenAsterisk(int length) {
    std::string ret = "*";
    for(int i = 0; i < length -2; i++)
        ret += " ";
    ret += "*\n";
    return ret;
}

const std::string Stat::printBoxedTitle(int length) {
    std::string ret = "";

    ret += fillAsterisk(length);
    ret += spacesBetweenAsterisk(length);
    ret += wrapMessage("Statistics", length);
    ret += spacesBetweenAsterisk(length);
    ret += fillAsterisk(length);
    ret += spacesBetweenAsterisk(length);

    return ret;
}

#include "../header/Stat.h"

#include <string>

Stat::Stat() {
    num_of_max_turns = 0;
    games.resize(10000);
    for(auto v : games)
        v.resize(0);
}

void Stat::feed(int num_of_turns, std::vector<Card> cards) {
    games.at(num_of_turns).push_back(cards);
    if(num_of_turns > num_of_max_turns)
        num_of_max_turns = num_of_turns;
}

void Stat::fillFrequences() {
    for(int i = 0; i <= num_of_max_turns; i++){
        if(games.at(i).size() != 0) {
            frequences.push_back(std::pair(i, games.at(i).size()));
        }
    }
}

unsigned long int Stat::numberOfGames() {
    unsigned long int number_of_games = 0;
    for (int i = 0; i <= num_of_max_turns; i++)
        if(games.at(i).size() != 0)
            number_of_games+=games.at(i).size();

    return number_of_games;
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

std::pair<int, std::vector<std::vector<Card>>> Stat::longestGame() {
    return std::pair(num_of_max_turns, games.at(num_of_max_turns));
}

std::vector<std::pair<int, std::vector<std::vector<Card>>>> Stat::gamesLongerThan(int min) {
    if(min > num_of_max_turns)
        throw "There are no games that lasted that many turns";

    std::vector<std::pair<int, std::vector<std::vector<Card>>>> ret;
    for(int i = min; i <= num_of_max_turns; i++) {
        if(games.at(i).size() != 0)
            ret.push_back(std::pair(i, games.at(i)));
    }
    return ret;
}

std::string Stat::longestGameToString(){
    std::string ret = "";

    for(auto card : games.at(num_of_max_turns).at(0)) 
        ret += card.toString();

    return ret;
}

std::string Stat::displayTable() {
    std::string ret = "number of turns | number of games \n";

    for(int i = 0; i <= num_of_max_turns; i++) {
        if(games.at(i).size() != 0){
            std::string line;
            line.resize(20);
            line.insert(0, std::to_string(i));
            line.insert(8, " ");
            line.insert(10, std::to_string(games.at(i).size()));
            line += "\n";
            ret += line;
        }
    }
    return ret;
}

void Stat::printTable(std::ostream& os) {
    os << displayTable();
}
 
void Stat::reset() {
    games.clear();
    games.resize(10000);
    for(auto v : games)
        v.resize(0);

    num_of_max_turns = 0;
    frequences.resize(0);
}
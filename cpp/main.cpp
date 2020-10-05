#include "tests/test_deck.h"
#include "tests/test_player.h"
#include "tests/test_game.h"

#include "header/Game.h"
#include "header/Deck.h"
#include "header/Card.h"
#include "header/NGames.h"
#include "header/ThreadStat.h"
#include "header/GlobalStat.h"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <ostream>
#include <functional>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

void playNGames() {
	Deck deck;

	unsigned int thread_num = 1;
	// std::thread::hardware_concurrency();
	int games_num = 1;
	bool exit = true;

	while (exit) {

		std::cout << "How many games would you like to play? ";

		std::cin >> games_num;
		// std::cout << "Number of Threads you can get is: " << thread_num << std::endl;
 
		std::cout << "How many threads? ";

		std::cin >> thread_num;

		NGames games;
		games.initialize(games_num, deck, thread_num);

		games.playGames();

		std::cout << games.stat.getCompTime() / 1000000.0 << std::endl;

		std::cout << games.stat.toString();

		std::cout << "0: Exit, 1: Continue " << std::endl;
		std::cin >> exit;
	}
}


void playNGamesMTimes(int num_of_games, int num_of_times, int min_thread_num, int max_thread_num, ThreadStat& threadStat) {
	Deck deck;
	NGames games;
	for(int i = min_thread_num; i <= max_thread_num; i++) {
		for(int j = 0; j < num_of_times; j++){
			games.initialize(num_of_games, deck, i);
			games.playGames();
			threadStat.feedThreadStat(i, games.stat.getCompTime());
		}
		std::cout << "Games played with " << i << " threads have been completed" << std::endl;
	}
}

void playNGamesMTimesForEachNumberOfThreads(){
/*
	int num_of_games = 1;
	int num_of_times = 1;
	int min_thread_num = 1;
	int max_thread_num = 1;
 
	std::cout << "For how many games would you like to test? " ;
	std::cin >> num_of_games;

	std::cout << "How many times per each threads size should all these games be played? ";
	std::cin >> num_of_times;

	std::cout << "What is the minimum number of threads you wanna test? ";
	std::cin >> min_thread_num;

	std::cout << "What is the maximum number of threads you wanna test? ";
	std::cin >> max_thread_num;

	ThreadStat threadStat;

	playNGamesMTimes(num_of_games, num_of_times, min_thread_num, max_thread_num, threadStat);
	*/

	ThreadStat threadStat;	

	playNGamesMTimes(1000, 20, 1, 20, threadStat);
	playNGamesMTimes(1000, 20, 300, 320, threadStat);

	threadStat.computeTimeMean();
	threadStat.num_of_games = 1000;
	std::cout << threadStat.toString();

	std::fstream f;
	f.open("stat2.txt", std::fstream::in | std::fstream::out);
	f << threadStat.toString();
	f.close();
}

class Handler{
	NGames games;
	GlobalStat globalStat;
	std::string globalStatFileName;
	std::string statTableFileName;

public:

	Handler(std::string _globalStatFileName, std::string _statTableFileName) : globalStatFileName(_globalStatFileName), statTableFileName(_statTableFileName) {
		std::cout << "Loading Statistics..." << std::endl;
		deserializeGlobalStat();
	}

	int askForNumberOfGames() {
		int num_of_games = 1;

		std::cout << "How many games do you wanna play? ";
		std::cin >> num_of_games;

		return num_of_games;
	}

	int askForNumberOfThreads() {
		int num_of_threads = 1;

		std::cout << "With how many threads? ";
		std::cin >> num_of_threads;

		return num_of_threads;
	}

	bool deserializeGlobalStat() {
		std::ifstream ifs(globalStatFileName, std::ios_base::binary | std::ios_base::in);
		if(ifs.is_open() == true){
			boost::archive::binary_iarchive ia(ifs);
			ia >> globalStat;
			return true;
		}
		return false;
	}
	
	void serializeGlobalStat(){
		std::cout << "Serializing global statistics..." << std::endl;

		std::ofstream ofs(globalStatFileName, std::ios_base::binary | std::ios_base::out);
		boost::archive::binary_oarchive oa(ofs);
		oa << globalStat;
	}

	void playNGamesWithoutThreads(){
		int num_of_games = askForNumberOfGames();

		Deck deck;
		games.initialize(num_of_games, deck);
		games.playGames();
		
		std::cout << games.stat.toString();

		globalStat.feed(games.stat);
		serializeGlobalStat();
	}

	void playNGamesWithThreads() {

		int num_of_games = askForNumberOfGames();
		int num_of_threads = askForNumberOfThreads();

		Deck deck;
		games.initialize(num_of_games, deck, num_of_threads);
		games.playGames();

		std::cout << games.stat.toString();

		globalStat.feed(games.stat);
		serializeGlobalStat();
	}

	void displayStatistics() {
		std::cout << globalStat.toString();
	}

	void displayDeckWithMaximumNumOfTurns() {
		std::cout << globalStat.longestGameToString() << std::endl;
	}

	void displayTable() {
		std::cout << globalStat.displayTable() << std::endl;
	}

	void printTable() {
		std::ofstream os(statTableFileName, std::ofstream::out);
		globalStat.printTable(os);
		os.close();
	}

	int askForInput() {
		int choice = 0;

		std::cout << "What do you wanna do? " << std::endl;
		std::cout << "0: Exit" << std::endl;
		std::cout << "1: Play N games without threading" << std::endl;
		std::cout << "2: Play N games with M threads" << std::endl;
		std::cout << "3: Display statistics" << std::endl;
		std::cout << "4: Display one of the decks with the maximum number of turns" << std::endl;
		std::cout << "5: Display the table: number of turns | number of occurences" << std::endl;
		std::cout << "6 Print table with number of turns and number of occurences into .txt file" << std::endl;

		std::cin >> choice;

		return choice;
	}

	void takeAction(int choice) {
		switch(choice) {
			case 0:
				break;
			case 1:
				playNGamesWithoutThreads();
				break;
			case 2:
				playNGamesWithThreads();
				break;
			case 3:
				displayStatistics();
				break;
			case 4:
				displayDeckWithMaximumNumOfTurns();
				break;
			case 5:
				displayTable();
			case 6:
				printTable();
				break;
			default:
				std::cout << "Wrong Selection!!!" << std::endl;
		}
	}

	void askAndDo() {
		int choice = 0;
		do {		
			choice = askForInput();
			
			takeAction(choice);
			
		}while(choice != 0);
	}

};
/*
int main() {
	NGames games;
	GlobalStat globalStat;
	Handler handler;
	std::string statFileName = "globalStat";
	int num_of_games = 1;

	if(handler.deserializeGlobalStat(globalStat, statFileName))
		std::cout<<globalStat.toString();

	std::cout << "How many games do you wanna play? ";
	std::cin >> num_of_games;

	handler.playNGamesWithoutThreads(games, num_of_games);

	globalStat.feed(games.stat);

	handler.serializeGlobalStat(globalStat, statFileName);

	std::cout << globalStat.toString();
}
*/

int main() {
	Handler handler("globalStat", "stat_table.txt");

	handler.askAndDo();
}
#include "tests/test_deck.h"
#include "tests/test_player.h"
#include "tests/test_game.h"

#include "header/Game.h"
#include "header/Deck.h"
#include "header/Card.h"
#include "header/NGames.h"
#include "header/ThreadStat.h"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <ostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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

		std::cout << games.stat;

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

void playAndSerialize() {
	Deck deck;
	int games_num = 1;

	NGames games;

	std::cout << "How many games would you like to play? ";

	std::cin >> games_num;
	// std::cout << "Number of Threads you can get is: " << thread_num << std::endl;

	games.initialize(games_num, deck);

	games.playGames();

	std::cout << games.stat;

	std:: cout << "Serializing the data...." <<std::endl;

	std::ofstream ofs("stat");
	// save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << games;
    	// archive and stream closed when destructors are called
    }

}

void readSerialization() {
	std::cout << "Reading Serialization.... " << std::endl;

	NGames games;
	{
        // create and open an archive for input
        std::ifstream ifs("stat");
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> games;
        // archive and stream closed when destructors are called
    }
	std::cout << games.stat;

}

int main() {
	playAndSerialize();

	readSerialization();
}

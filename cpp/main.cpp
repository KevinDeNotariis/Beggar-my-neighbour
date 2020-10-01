#include "tests/test_deck.h"
#include "tests/test_player.h"
#include "tests/test_game.h"

#include "header/Game.h"
#include "header/Deck.h"
#include "header/Card.h"
#include "header/NGames.h"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <ctime>
#include <chrono>

/*
int main() {

	Deck deck;
	Game game;

	Player p1;
	Player p2;

	std::map<int,int> stat;

	for(int i = 0; i < 1000; i++){
		game.initialize(deck);

		p1 = game.player1;
		p2 = game.player2;

		game.play();

		if(stat.find(game.num_of_turns) != stat.end())
			stat[game.num_of_turns]++;
		else
			stat.insert(std::pair(game.num_of_turns, 1));
	}
}*/

int main() {
	Deck deck;

	int thread_num = 1;
	int games_num = 1;
	bool exit = true;

	while (exit) {

		std::cout << "How many games would you like to play? ";

		std::cin >> games_num;

		std::cout << "How many threads? ";

		std::cin >> thread_num;

		NGames games(games_num, deck, thread_num);

		games.playGames();

		std::cout << games.stat.getCompTime() / 1000000.0 << std::endl;

		std::cout << "0: Exit, 1: Continue " << std::endl;
		std::cin >> exit;
	}
}
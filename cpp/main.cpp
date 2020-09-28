#include "tests/test_deck.h"
#include "tests/test_player.h"
#include "tests/test_game.h"

#include "header/Game.h"
#include "header/Deck.h"
#include "header/Card.h"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>


int main() {
	//test_deck();
	//test_player();
	//test_game();

	Deck deck;
	Game game;

	Player p1;
	Player p2;

	std::map<int,int> stat;

	for(int i = 0; i < 100000; i++){
		game.initialize(deck);

		p1 = game.player1;
		p2 = game.player2;

		game.play();

		if(stat.find(game.num_of_turns) != stat.end())
			stat[game.num_of_turns]++;
		else
			stat.insert(std::pair(game.num_of_turns, 1));
	}

	/*std::fstream f;
	f.open("stat.txt", std::fstream::in | std::fstream::out);

	for(auto& [key,value] : stat) {
		f << key << "\t" << value << std::endl;
	}
	f.close(); */
}
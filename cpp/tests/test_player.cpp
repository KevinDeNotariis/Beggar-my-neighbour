#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>

#include "test_player.h"

#include "../header/Deck.h"
#include "../header/Card.h"
#include "../header/Player.h"
#include "MyTest.h"

void test_player() {
	MyTest test("Testing Player Class");

	Deck deck;
	std::vector<Card> starting_cards(deck.cards.begin(), deck.cards.begin() + 20);

	Player player;
	
	test.set_up = [&player, starting_cards] {
		player.initialize(starting_cards);
	};
	
	test.set_up();

	test.add_test(test.assert_true(
		"Test whether a default-constructed player got a non-empty set of cards",
		"Player should have some cards at the start of the game",
		[player] { return player.cards.size() !=  0; }
	));

	test.add_test(test.assert_true(
		"Test whether a player got 20 cards at the start of the game",
		"Player should have 20 cards at the start of the game",
		[player] { return player.cards.size() == 20; }
	));

	test.add_test(test.assert_true(
		"Test whether the player got indeed Cards",
		"Player should have Cards not something else",
		[player] {
			return typeid(player.cards.at(1)) == typeid(Card); }
	));

	test.add_test(test.assert_false(
		"Test whether we could play a card from the top, namely if we put a (1, swords) on top and we use playTop, then it should disappear from the cards of the player",
		"playTop need to play the (1, swords), so it must be removed from the cards list",
		[&player] {
			player.playTop();
			return player.playTop() == Card(1, "swords");
		}
	));

	test.add_test(test.assert_true(
		"Test if the number of cards is diminished after the player played the top card with playTop",
		"playTop need to diminish the number of cards of the player",
		[&player] {
			unsigned number_of_cards = player.cards.size();
			player.playTop();
			return player.cards.size() == (number_of_cards-1);
		}
	));

	test.add_test(test.assert_true(
		"Test whether the returned card from playTop after putting (4, clubs) on top, is the right indeed the (4, clubs)",
		"The returned card should be the (4, clubs)",
		[&player] {
			player.cards.push_back(Card(4, "clubs"));
			return player.playTop() == Card(4, "clubs");
		}
	));

	test.add_test(test.assert_true(
		"Test whether the putUnder increases the number of cards of the player",
		"putUnder should increase the number of cards of the player",
		[&player] {
			unsigned number_of_cards = player.cards.size();
			player.putUnder(Card(2, "swords"));
			return player.cards.size() == (number_of_cards+1);
		}
	));

	test.add_test(test.assert_true(
		"Test whether the card at the bottom is the one put by putUnder method, namely if we putUnder a (6, coins), then at cards.at(0) there should be that card",
		"At card.at(0) there should be the card put by putUnder",
		[&player] {
			player.putUnder(Card(6, "coins"));
			return player.cards.at(0) == Card(6, "coins");
		}
	));

	test.add_test(test.assert_true(
		"Test whether after putUnder, the other cards are still unchanged",
		"The rest of the cards after putUnder are not unchanged",
		[&player] {
			std::vector<Card> unchanged_cards = player.cards;
			player.putUnder(Card(8, "clubs"));
			return  ((std::vector<Card>(player.cards.begin() + 1, player.cards.end()) == unchanged_cards));
		}
	));

	test.add_test(test.assert_true(
		"Test whether after put under a bunch of cards (in a vector), the size of the cards of the player is increased accordingly, namely after putting a vector of 3 cards, the number of cards should be increased by 3",
		"The number of cards after putUnder is not increased in the right way",
		[&player] {
			std::vector<Card> cards_to_put_under{ Card(2, "swords"), Card(4, "cups"), Card(9, "coins") };
			unsigned number_of_cards = player.cards.size();
			player.putUnder(cards_to_put_under);
			
			return player.cards.size() == (number_of_cards + 3);
		}
	));

	test.add_test(test.assert_true(
		"Test whether after put under the following cards in this order [(2, swords),(6, clubs),(3, cups)] then these should be put under in the same order",
		"The cards were not put in the right order",
		[&player] {
			std::vector<Card> cards_to_put_under{ Card(2, "swords"), Card(6, "clubs"), Card(3, "cups") };
			player.putUnder(cards_to_put_under);

			return ((player.cards.at(0) == Card(2, "swords")) && (player.cards.at(1) == Card(6, "clubs")) && (player.cards.at(2) == Card(3, "cups")));
		}
	));

	test.add_test(test.assert_true(
		"Test whether after putUnder the following cards in this order [(2, swords),(6, clubs),(3, cups)] then these should be put under in the reversed order if the specification \"reversed\" is put in the function call",
		"The cards from putUnder were not put in the reverse order",
		[&player] {
			std::vector<Card> cards_to_put_under{ Card(2, "swords"), Card(6, "clubs"), Card(3, "cups") };
			player.putUnder(cards_to_put_under, "reversed");

			return (
				(player.cards.at(0) == Card(3, "cups")) && 
				(player.cards.at(1) == Card(6, "clubs")) && 
				(player.cards.at(2) == Card(2, "swords"))
			);
		}
	));

	test.add_test(test.assert_false(
		"Test whether two players with different cards are indeed different, i.e. not equal",
		"The players should not be equal",
		[deck] {
			Player player1;
			Player player2;
			player1.initialize(std::vector<Card>(deck.cards.begin(), deck.cards.begin()+10));
			player2.initialize(std::vector<Card>(deck.cards.begin()+20, deck.cards.begin()+30));

			return player1 == player2;
		}
	));

	test.run();
}
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#include "test_deck.h"

#include "MyTest.h"
#include "../header/Card.h"
#include "../header/Deck.h"


void test_deck() {

	MyTest test("Testing Deck Class");

	Deck deck;

	test.set_up = [&deck] { deck.initialize(); };

	test.set_up();

	test.add_test(test.assert_false(
		"Test if isNotEmpty return true for default-constructed deck",
		"Deck should be initialised not empty",
		[deck] { return deck.isEmpty(); }
	));

	test.add_test(test.assert_true(
		"Test whether deck contains 40 cards after default construction",
		"Deck should contain 40 cards",
		[deck] { return deck.cards.size() == 40; }
	));

	test.add_test(test.assert_true(
		"Test if there exist the (1, swords) card for a default-constructed deck",
		"Deck should contain the (1, swords) card",
		[deck] { return deck.contains(Card(1, "swords")); }
	));

	test.add_test(test.assert_false(
		"Test whether the deck contains a (22, coins) card for a default-constructed deck",
		"Deck should not contain the (22, coins) card, since it is a 40 cards deck",
		[deck] { return deck.contains(Card(22, "coins")); }
	));

	test.add_test(test.assert_true(
		"Test whether size() returns 40 for a default constructed deck",
		"size() should return 40",
		[deck] { return deck.size() == 40; }
	));

	test.add_test(test.assert_true(
		"Test whether after popping the last card, the number of remaining cards is diminished by 1, namely from 40 to 39 for a default-constructed deck",
		"After popping last card, the number of cards should be 39",
		[&deck] {
			Card card = deck.popLast();
			return deck.size() == 39;
		}
	));

	test.add_test(test.assert_true(
		"Test whether deck isEmpty after popping all cards",
		"Deck should be empty after popping all cards",
		[&deck] {
			for (int i = 0; i < 40; i++)
				deck.popLast();

			return deck.isEmpty();
		}
	));

	test.add_test(test.assert_true(
		"Test whether popLast return correctly the (10, cups) for a default constructed deck",
		"The card popped should be the (10, cups)",
		[&deck] {
			return deck.popLast() == Card(10, "cups");
		}
	));

	test.run();
}


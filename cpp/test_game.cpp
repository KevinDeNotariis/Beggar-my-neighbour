#include "test_game.h"
#include "MyTest.h"
#include "Game.h"
#include "Deck.h"
#include "Card.h"

#include <map>
#include <algorithm>
#include <iostream>

void test_game() {
    MyTest test("Testing Game Class");

    Deck deck;
    Game game;

    test.set_up = [&game, deck]{
        game.initialize(deck);
    };

    test.set_up();

    test.add_test(test.assert_true(
        "Testing whether at the start of the game, each player has 20 cards",
        "Each player should have 20 cards at the start of the game",
        [game] {
            return (
                (game.player1.cards.size() == 20) &&
                (game.player2.cards.size() == 20)
            );
        }
    ));

    test.add_test(test.assert_true(
        "Test whether the assigned cards are actually different, namely see whether each player has a unique set of 20 cards",
        "Each player should have a unique set of 20 cards!",
        [game] {
            for(Card player1_cards : game.player1.cards) {
                if(std::find(game.player2.cards.begin(), game.player2.cards.end(), player1_cards) != game.player2.cards.end())
                return false;
            }
            return true;
        }
    ));

    test.add_test(test.assert_true(
        "Test whether after the active_player has played a card, the table size increases by 1",
        "The table size should increase after a card is played",
        [&game] {
            unsigned table_size_before = game.table.size();
            game.activePlayerPlaysOneCard();
            return table_size_before+1 == game.table.size();
        }
    ));

    test.add_test(test.assert_false(
        "Test whether after a player - not paying - played a normal card (not special, i.e. 1, 2 and 3), then turn should pass to the other player",
        "The active_player should change after playing a normal card",
        [&game] {
            Player *active_player_before = game.active_player;
            game.activePlayerPlaysOneCard();
            return (*active_player_before == *game.active_player);
        }
    ));

    test.add_test(test.assert_true(
        ""
    ));

    /*
    test.add_test(test.assert_true(
        "Test whether after the top card of player1 is played, the table size is increased by one.",
        "The table size should increase after player1 played a card",
        [&game] {
            unsigned table_size_before = game.table.size();
            game.player1PlaysOneCard();

            return game.table.size() == table_size_before+1; 
        }
    ));
    test.add_test(test.assert_true(
        "Test whether after the top card of player2 is played, the table size is increased by one.",
        "The table size should increase after player2 played a card",
        [&game] {
            unsigned table_size_before = game.table.size();
            game.player2PlaysOneCard();

            return game.table.size() == table_size_before+1; 
        }
    ));
    */

    test.run();
}
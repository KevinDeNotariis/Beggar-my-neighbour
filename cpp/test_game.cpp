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

    test.add_test(test.assert_true(
        "Test whether after takeProfit, the non-active player has gained the cards in the table",
        "The non-active player should take the cards in the table",
        [&game] {
            game.table.push_back(Card(8, "clubs"));
            game.table.push_back(Card(4, "swords"));

            game.takeProfit();

            return (
                (game.non_active_player->cards.at(0) == Card(4, "swords")) &&
                (game.non_active_player->cards.at(1) == Card(8, "clubs"))
            );
        }
    ));

    test.add_test(test.assert_true(
        "Test whether after takeProfit, the table has been reset to size 0",
        "The table should be reset after takeProfit",
        [&game] {
            game.table.push_back(Card(8, "clubs"));
            game.table.push_back(Card(4, "swords"));

            game.takeProfit();

            return game.table.size() == 0;
        }
    ));

    test.add_test(test.assert_true(
        "Test whether after a penalty card, say (2, clubs), has been played, then the non active player should play. in principle, two cards. Namely the penalty variable should be equals to the penalty",
        "The penalty variable should store the penalty to pay",
        [&game] {
            game.active_player->cards.resize(0);
            game.active_player->cards.push_back(Card(2, "clubs"));

            game.activePlayerPlays();

            return game.penalty_to_pay == 2;
        }
    ));

    test.add_test(test.assert_true(
        "Test whether when penalty is not zero, the active player should play the number of cards specified in penalty",
        "The active player should pay the penalty",
        [&game] {
            game.active_player->cards.resize(0);
            game.active_player->cards.push_back(Card(2, "clubs"));
            game.non_active_player->cards.push_back(Card(4, "swords"));
            game.non_active_player->cards.push_back(Card(5, "clubs"));

            Player *paying_player = game.non_active_player;
            unsigned cards_size_before = paying_player->cards.size();

            game.activePlayerPlays();

            game.activePlayerPlays();

            return paying_player->cards.size() == cards_size_before-2;
        }
    ));

    test.add_test(test.assert_true(
        "Test whether after one player takes profit, the penalty is indeed reset to 0",
        "The penalty should be reset after takeProfit",
        [&game] {
            game.active_player->cards.resize(0);
            game.active_player->cards.push_back(Card(2, "clubs"));
            game.non_active_player->cards.push_back(Card(4, "swords"));
            game.non_active_player->cards.push_back(Card(5, "clubs"));

            game.activePlayerPlays();

            game.activePlayerPlays();

            game.takeProfit();

            return game.penalty_to_pay == 0;
        }
    ));

    test.add_test(test.assert_true(
        "Test whether after a player has finished paying his debt - without having played any penalty cards - the other player takes the profit",
        "The non_active_player should take the profit after the paying player has finished paying",
        [&game] {
            game.active_player->cards.resize(0);
            game.active_player->cards.push_back(Card(2, "clubs"));

            Player *player_that_will_take_profit = game.active_player;

            game.non_active_player->cards.push_back(Card(4, "swords"));
            game.non_active_player->cards.push_back(Card(5, "clubs"));

            game.activePlayerPlays();

            game.activePlayerPlays();

            return player_that_will_take_profit->cards.size() == 3;
        }
    ));

    test.add_test(test.assert_true(
        "Test whether when a player paying plays a penalty card, then the control switch to the other player that must start to pay",
        "The active_player should switch immediately after a paying player plays a penalty card",
        [&game] {
            game.active_player->cards.resize(0);
            game.active_player->cards.push_back(Card(2, "clubs"));
            Player *initial_player = game.active_player;

            game.non_active_player->cards.push_back(Card(1, "coins"));

            game.activePlayerPlays();

            game.activePlayerPlays();

            return (
                *game.active_player == *initial_player &&
                game.table.size() == 2
            );
        }
    ));

    test.add_test(test.assert_true(
        "Test whether after a player plays a non penalty card and the they have no more cards, the game finishes",
        "The variable end_game should become true whenever a player finishes their cards after putting down a non penalty card",
        [&game] {
            game.active_player->cards.resize(0);
            game.active_player->cards.push_back(Card(4, "clubs"));

            game.activePlayerPlays();

            return game.end_game == true;
        }
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
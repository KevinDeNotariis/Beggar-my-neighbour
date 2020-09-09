import unittest
import numpy as np


from deck import Deck
from deck import Card
from game import Player
from game import Game


class TestPlayer(unittest.TestCase):

    def setUp(self):
        self.player = Player()
        self.game = Game()

    def test_is_Empty(self):
        self.assertEqual(len(self.player.stack_of_cards), 0)

    def test_oneCardLess_AfterPlayingTopCard(self):
        self.player.stack_of_cards.append(Card(9,"swords"))
        self.player.stack_of_cards.append(Card(9, "clubs"))
        self.player.playTopCard()
        self.assertEqual(len(self.player.stack_of_cards), 1)

    def test_havePlayersHalfDeck(self):
        self.assertEqual(len(self.game.player1.stack_of_cards), 20)
        self.assertEqual(len(self.game.player2.stack_of_cards), 20)

    def test_hasTableOneCardAfterPlayerPlayedIt(self):
        self.game.playCard()
        self.assertEqual(len(self.game.table), 1)
        
    def test_TableGotOneCardFromPlayer(self):
        self.game.table = []
        self.game.player1.stack_of_cards = [Card(9, "swords")]

        self.game.playCard()

        self.assertEqual(self.game.table[0], Card(9, "swords"))
        self.assertEqual(len(self.game.player1.stack_of_cards), 0)

    def test_playCardTwice_TableGotTwoCardsFromDifferentPlayers(self):
        self.game.table = []
        self.game.player1.stack_of_cards = [Card(9, "swords")]
        self.game.player2.stack_of_cards = [Card(9, "clubs")]

        self.game.playCard()
        self.game.playCard()

        self.assertEqual(self.game.table[0], Card(9, "swords"))
        self.assertEqual(self.game.table[1], Card(9, "clubs"))

    def test_doesPlayerPlayAgainIfSpecialCardWasPlayed(self):
        self.game.table = []
        self.game.player1.stack_of_cards = [Card(2, "swords")]
        self.game.player2.stack_of_cards = [Card(7, "clubs"), Card(5, "coins")]

        self.game.playCard()
        self.game.playCard()
        self.game.playCard()

        self.assertEqual(self.game.table, [Card(2, "swords"), Card(5, "coins"), Card(7, "clubs")])

if __name__ == "__main__" :
    unittest.main()
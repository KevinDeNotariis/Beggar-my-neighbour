import numpy as np
from deck import Deck
from deck import Card

class Player:

    def __init__(self):
        self.stack_of_cards = []
        self.cardsToPutDown = 1

    def playCards(self):
        cards = []
        for i in range(0, self.cardsToPutDown):
            cards.append(self.playTopCard())
            if cards[len(cards) - 1].value in [1, 2, 3]:
                return cards
            #elif len(self.stack_of_cards) == 0:
            #    endGame()
        return cards    
        

    def playTopCard(self):
        print(self.stack_of_cards)
        return self.stack_of_cards.pop(len(self.stack_of_cards)-1)

    def print(self):
        for i in range(0, len(self.stack_of_cards)):
            print(self.stack_of_cards[i])

    

class Game:

    def __init__(self):
        self.deck = Deck()
        self.table = []
        self.player1 = Player()
        self.player2 = Player()
        self.turn = self.player1
        self.offTurn = self.player2
        self.player1.stack_of_cards = self.deck.cards[0: 20]
        self.player2.stack_of_cards = self.deck.cards[20:40]

    def exchangePriority(self):
        if self.turn == self.player1:
            self.turn = self.player2
            self.offTurn = self.player1
        else:
            self.turn = self.player1
            self.offTurn = self.player2


    def playCard(self):
        if len(self.turn.stack_of_cards) > 0:
            cards = self.turn.playCards()
            for card in cards:
                self.table.append(card)
        else:
            endGame()

        self.offTurn.cardsToPutDown = self.table[len(self.table) - 1].value

        self.exchangePriority()
        
def endGame():
    print("END GAME")


# game = Game()
# print("player 1 cards: \n")
# game.player1.print()
# print("player 2 cards: \n")
# game.player2.print()
# print(game.player1.stack_of_cards.pop())
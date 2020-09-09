import numpy as np


class Card:
    def __init__(self, value, suit):
        self.value = value
        self.suit = suit

    def __repr__(self):
        return "(" + str(self.value) + ", " + self.suit + ")"

    def __eq__(self, card):
        if(self.value == card.value and self.suit == card.suit):
            return True
        return False

class Deck:
    cards = []

    def __init__(self):
        for suit in ["coins", "cups", "swords", "clubs"]:
            for i in range(1, 11):
                self.cards.append(Card(i, suit))

    def shuffle(self):
        np.random.shuffle(self.cards)
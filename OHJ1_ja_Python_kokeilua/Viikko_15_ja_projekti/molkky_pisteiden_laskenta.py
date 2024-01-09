"""
COMP.CS.100 Ohjelmointi 1 / Programming 1

Code template for Mölkky.

Lassi Lappalainen
Opiskelijanumero: 150390123
"""


# TODO:
class Player:

    def __init__(self, name):
        self.__name = name
        self.__pts = 0
        self.__average = 0
        self.__throw = 0
        self.__hit_percentage = 0.0

    def get_name(self):
        return self.__name

    def add_points(self, pts):
        self.__pts += pts
        if self.__pts > 50:
            print(f"{self.__name} gets penalty points!")
            self.__pts = 25
        if 40 <= self.__pts < 50:
            points = 50 - self.__pts
            print(f"{self.__name} needs only {points}"
                  f" points. It's better to avoid "
                  f"knocking down the pins with higher points.")
        if pts >= 1:
            self.__hit_percentage += 1

        return self.__pts

    def has_won(self):
        if self.__pts == 50:
            return True

        else:
            pass

    def get_points(self):
        return self.__pts

    def average(self, pts):
        self.__throw += 1
        self.__average += pts
        average = self.__average / self.__throw
        if pts > average and self.__throw > 1:
            print(f"Cheers {self.__name}!")
        return

    def hit_percentage(self):

        if self.__throw == 0:
            return self.__hit_percentage

        percentage = (self.__hit_percentage / self.__throw) * 100
        percentage = f"{percentage:.1f}"

        return percentage


def main():

    player1 = Player("Matti")
    player2 = Player("Teppo")

    throw = 1
    while True:

        if throw % 2 == 0:
            in_turn = player1

        else:
            in_turn = player2

        pts = int(input("Enter the score of player " + in_turn.get_name() +
                        " of throw " + str(throw) + ": "))

        in_turn.add_points(pts)
        in_turn.average(pts)

        if in_turn.has_won():
            print("Game over! The winner is " + in_turn.get_name() + "!")
            return

        print("")
        print("Scoreboard after throw " + str(throw) + ":")
        print(player1.get_name() + ":", player1.get_points(), "p", end=", ")
        print(f"hit percentage", player1.hit_percentage())
        print(player2.get_name() + ":", player2.get_points(), "p", end=", ")
        print(f"hit percentage", player2.hit_percentage())
        print("")

        throw += 1


if __name__ == "__main__":
    main()

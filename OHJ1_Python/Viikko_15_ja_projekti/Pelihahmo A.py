"""
COMP.CS.100 Ohjelmointi 1 / Programming 1

This program models a character adventuring in a video game,
or more like, the stuff that the character carries around.

Lassi Lappalainen
Opiskelijanumero: 150390123
"""

class Character:


    def __init__(self, name):
        self.name = name
        self.item_list = []
        self.item_list_once = []

        return

    def printout(self):

        if not self.item_list_once:
            print(f"Name: {self.name}")
            print("  --nothing--")
            return

        print(f"Name: {self.name}")

        self.item_list_once = sorted(self.item_list_once)

        for n in range(0, len(self.item_list_once)):

            many = self.item_list.count(self.item_list_once[n])

            print(f"  {many} {self.item_list_once[n]}")

        return

    def remove_item(self, item):

        if item in self.item_list:
            if self.item_list.count(item) == 1:
                self.item_list_once.remove(item)
        if item in self.item_list:
            self.item_list.remove(item)

        else:
            return

    def give_item(self, item):

        if item not in self.item_list:
            self.item_list_once.append(item)
        self.item_list.append(item)
        return

    def how_many(self, item):

        if self.item_list.count(item) >= 0:
            return self.item_list.count(item)
        else:
            return

    def has_item(self, item):
        if item in self.item_list_once:
            return True
        return False

    def get_name(self):
        return self.name



def main():
    character1 = Character("Conan the Barbarian")
    character2 = Character("Deadpool")

    for test_item in ["sword", "sausage", "plate armor", "sausage", "sausage"]:
        character1.give_item(test_item)

    for test_item in ["gun", "sword", "gun", "sword", "hero outfit"]:
        character2.give_item(test_item)

    character1.remove_item("sausage")
    character2.remove_item("hero outfit")

    character1.printout()
    character2.printout()

    for hero in [character1, character2]:
        print(f"{hero.get_name()}:")

        for test_item in ["sausage", "sword", "plate armor", "gun", "hero outfit"]:
            if hero.has_item(test_item):
                print(f"  {test_item}: {hero.how_many(test_item)} found.")
            else:
                print(f"  {test_item}: none found.")


if __name__ == "__main__":
    main()

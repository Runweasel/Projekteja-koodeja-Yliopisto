"""
COMP.CS.100 Ohjelmointi 1 / Programming 1

This program models a character adventuring in a video game.

Lassi Lappalainen
Opiskelijanumero: 150390123
"""


class Character:
    """
    This class defines what a character is int he game and what
    he or she can do.
    """

    # TODO: copy your Character class implementation from
    #       the previous assignment here and implement the
    #       following new methods.
    #
    #       Also note, that you have to modify at least
    #       __init__ and printout methods to conform with
    #       the new bahavior of the class.


    def __init__(self, name, health):
        self.name = name
        self.item_list = []
        self.item_list_once = []
        self.health_points = health

        return

    def printout(self):

        if not self.item_list_once:
            print(f"Name: {self.name}")
            print("  --nothing--")
            return

        print(f"Name: {self.name}")
        print(f"Hitpoints: {self.health_points}")

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
            how = self.item_list.count(item)
            return how
        else:
            return

    def has_item(self, item):
        if item in self.item_list_once:
            return True
        return False

    def get_name(self):
        return self.name

    def pass_item(self, item, target):
        """
        Passes (i.e. transfers) an item from one person (self)
        to another (target).

        :param item: str, the name of the item in self's inventory
                     to be given to target.
        :param target: Character, the target to whom the item is to
                     to be given.
        :return: True, if passing the item to target was successful.
                 False, it passing the item failed for any reason.
        """

        # TODO: implementation of the

        if item not in self.item_list:
            return

        if item in self.item_list:
            if self.item_list.count(item) == 1:
                self.item_list_once.remove(item)

        self.item_list.remove(item)
        target.item_list.append(item)
        if item not in target.item_list_once:
            target.item_list_once.append(item)


    def attack(self, target, weapon):
        """
        A character (self) attacks the target using a weapon.
        This method will also take care of all the printouts
        relevant to the attack.

        There are three error conditions:
          (1) weapon is unknown i.e. not a key in WEAPONS dict.
          (2) self does not have the weapon used in the attack
          (3) character tries to attack him/herself.
        You can find the error message to printed in each case
        from the example run in the assignment.

        The damage the target receives if the attack succeeds is
        defined by the weapon and can be found as the payload in
        the WEAPONS dict. It will be deducted from the target's
        hitpoints. If the target's hitpoints go down to zero or
        less, the target is defeated.

        The format of the message resulting from a successful attack and
        the defeat of the target can also be found in the assignment.

        :param target: Character, the target of the attack.
        :param weapon: str, the name of the weapon used in the attack
                       (must be exist as a key in the WEAPONS dict).
        :return: True, if attack succeeds.
                 False, if attack fails for any reason.
        """


        # TODO: the implementation of the method

        if weapon not in WEAPONS:
            print(f"Attack fails: unknown weapon \"{weapon}\".")
            return


        if weapon not in self.item_list_once:
            print(f"Attack fails: {self.name} doesn't have \"{weapon}\".")
            return


        if self.name == target.get_name():
            print(f"Attack fails: {self.name} can't attack him/herself.")
            return

        if weapon in WEAPONS:
            print(f"{self.name} attacks {target.get_name()} delivering {WEAPONS[weapon]} damage.")
            health = target.health_points - WEAPONS[weapon]
            target.health_points = health

            if health <= 0:
                print(f"{self.name} successfully defeats {target.get_name()}.")
            return




WEAPONS = {
    # Weapon          Damage
    # --------------   ------
    "elephant gun": 15,
    "gun": 5,
    "light saber": 50,
    "sword": 7,
}


def main():
    conan = Character("Conan the Barbarian", 10)
    deadpool = Character("Deadpool", 45)

    # Testing the pass_item method

    for test_item in ["sword", "sausage", "plate armor", "sausage", "sausage"]:
        conan.give_item(test_item)

    for test_item in ["gun", "sword", "gun", "sword", "hero outfit"]:
        deadpool.give_item(test_item)

    conan.pass_item("sword", deadpool)
    deadpool.pass_item("hero outfit", conan)
    conan.pass_item("sausage", deadpool)
    deadpool.pass_item("gun", conan)
    conan.pass_item("sausage", deadpool)
    deadpool.pass_item("gun", conan)

    print("-" * 5, "How are things after passing items around", "-" * 20)
    conan.printout()
    deadpool.printout()

    # Testing a fight i.e. the attack method

    print("-" * 5, "Let's see how a fight proceeds", "-" * 32)

    # Conan's turn
    conan.attack(deadpool, "sword")  # Conan doesn't have a sword.
    conan.attack(conan, "gun")  # A character is not allowed to attack himself.
    conan.attack(conan, "pen")  # Pen is not a known weapon in WEAPONS dict.
    conan.attack(deadpool, "gun")  # Attack with a gun.

    # Deadpool retaliates
    deadpool.attack(conan, "sword")  # Deadpool has a sword.

    # Conan's 2nd turn
    conan.attack(deadpool, "gun")  # Attack with a gun again.

    # Deadpool strikes back again and Conan drops "dead".
    deadpool.attack(conan, "sword")

    print("Are You Not Entertained?!")

    print("-" * 5, "How are things after beating each other up", "-" * 20)

    conan.printout()
    deadpool.printout()

    #result = test_pass_item()
    #print(result)


def test_pass_item():
    """
    tämän testin tekee automaatti-tarkastaja
    :return:
    """
    char1 = Character("Flashy Flash", 1)
    char2 = Character("Tanktop Master", 2)
    char1.give_item("monster cell")
    char1.give_item("monster cell")
    char1.give_item("sword")
    result = [char2.how_many("sword")]
    char1.pass_item("sword", char2)
    char1.pass_item("monster cell", char2)
    char1.pass_item("NON_EXISTING_ITEM", char2)
    result.append(char2.how_many("sword"))  # 1
    result.append(char1.how_many("sword"))  # 0
    result.append(char2.how_many("monster cell"))  # 1
    result.append(char1.how_many("monster cell"))  # 1
    result.append(char2.how_many("NON_EXISTING_ITEM"))  # 0
    return result


if __name__ == "__main__":
    main()

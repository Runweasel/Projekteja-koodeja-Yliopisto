"""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""


class Fraction:

    def __init__(self, numerator_self, denominator_self):
        """
        Constructor. Checks that the numerator and denominator are of
        correct type and initializes them.

        :param numerator_self: int, fraction's numerator
        :param denominator_self: int, fraction's denominator
        """

        if not isinstance(numerator_self, int) or not isinstance(denominator_self, int):
            raise TypeError

        elif denominator_self == 0:
            raise ValueError

        self.__numerator = numerator_self
        self.__denominator = denominator_self

    def return_string(self):
        """
        :returns: str, a string-presentation of the fraction in the format
                       numerator/denominator.
        """

        if self.__numerator * self.__denominator < 0:
            sign = "-"

        else:
            sign = ""

        return f"{sign}{abs(self.__numerator)}/{abs(self.__denominator)}"

    def simplify(self):
        """

        :return:
        """

        global numerator, denominator
        a = greatest_common_divisor(self.__numerator, self.__denominator)

        if self.__numerator % a == 0:
            numerator = self.__numerator // a

        if self.__denominator % a == 0:
            denominator = self.__denominator // a

        fraction_object = Fraction(numerator, denominator)
        return fraction_object

    def multiply(self, fraction_object2):

        numerator_object, denominator_object = fraction_object2.unpack_object()
        numerator_object = self.__numerator * numerator_object
        denominator_object = self.__denominator * denominator_object
        fraction_object = Fraction(numerator_object, denominator_object)
        return fraction_object

    def unpack_object(self):

        return self.__numerator, self.__denominator


def greatest_common_divisor(a, b):
    """
    Euclidean algorithm. Returns the greatest common
    divisor (suurin yhteinen tekijä).  When both the numerator
    and the denominator is divided by their greatest common divisor,
    the result will be the most reduced version of the fraction in question.
    """

    while b != 0:
        a, b = b, a % b

    return a


def read_input():
    """
    lukee käyttäjän syötteen ja palauttaa arvot
    :return:
    """

    global fraction_olio
    fraction_dic = {}

    while True:
        syote = input("> ")
        try:
            if syote == "add":

                fraction = input("Enter a fraction in the form integer/integer: ")
                fraction_list = [fraction]

                for n in range(0, 1):
                    fields = fraction_list[n].split("/")
                    numerator_field = int(fields[0])
                    denominator_field = int(fields[1])
                    fraction_olio = Fraction(numerator_field, denominator_field)

                name = input("Enter a name: ")

                update = {name: fraction_olio}
                fraction_dic.update(update)
                continue

            if syote == "quit":

                print("Bye bye!")
                return

            if syote == "print":
                name = input("Enter a name: ")
                if name in fraction_dic:
                    print(f"{name} = {fraction_dic.get(name).return_string()}")
                    continue
                else:
                    print(f"Name {name} was not found")
                continue

            if syote == "list":
                if not fraction_dic:
                    continue
                else:
                    for fraction in sorted(fraction_dic):
                        print(f"{fraction} = {fraction_dic.get(fraction).return_string()}")
                    continue

            if syote == "*":
                first = input("1st operand: ")
                if first not in fraction_dic:
                    print(f"Name {first} was not found")
                    continue
                first = fraction_dic.get(first)
                second = input("2nd operand: ")
                if second not in fraction_dic:
                    print(f"Name {second} was not found")
                    continue
                second = fraction_dic.get(second)
                multiplied = first.multiply(second)
                multiplied_arvo = multiplied.return_string()
                print(f"{first.return_string()} * {second.return_string()} ", end="")
                print(f"= {multiplied_arvo}")
                simplified = multiplied.simplify()
                print(f"simplified {simplified.return_string()}")
                continue

            if syote == "file":
                filename = input("Enter the name of the file: ")
                file_fractions = {}

                try:
                    file = open(filename, mode="r")
                except OSError:
                    print("Error: the file cannot be read.")
                    continue

                for line in file:
                    try:

                        fields = line.split("=")

                        name = fields[0]

                        fraction_list = [fields[1]]

                        for n in range(0, 1):
                            fields = fraction_list[n].split("/")
                            numerator_field = int(fields[0])
                            denominator_field = int(fields[1])
                            fraction_olio = Fraction(numerator_field, denominator_field)

                        update = {name: fraction_olio}
                        file_fractions.update(update)

                    except IndexError:
                        print("Error: the file cannot be read.")
                        continue

                fraction_dic.update(file_fractions)
                continue

            else:
                print("Unknown command!")
                pass

        except ValueError:
            pass


def main():

    read_input()


if __name__ == "__main__":
    main()

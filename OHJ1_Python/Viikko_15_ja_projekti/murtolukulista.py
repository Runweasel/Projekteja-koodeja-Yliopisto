"""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""


class Fraction:

    def __init__(self, numerator, denominator):
        """
        Constructor. Checks that the numerator and denominator are of
        correct type and initializes them.

        :param numerator: int, fraction's numerator
        :param denominator: int, fraction's denominator
        """

        if not isinstance(numerator, int) or not isinstance(denominator, int):
            raise TypeError

        elif denominator == 0:
            raise ValueError

        self.__numerator = numerator
        self.__denominator = denominator

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

        a = greatest_common_divisor(self.__numerator, self.__denominator)

        if self.__numerator % a == 0:
            numerator = self.__numerator // a

        if self.__denominator % a == 0:
            denominator = self.__denominator // a

        return f"{numerator}/{denominator}"



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

    fraction_list = []
    while True:
        fraction = input()
        try:
            if fraction == "":
                return fraction_list
            else:
                fraction_list.append(fraction)
                pass

        except ValueError:
            pass


def main():

    list = []
    simplified_list = []

    print("Enter fractions in the format integer/integer.")
    print("One fraction per line. Stop by entering an empty line.")

    fraction_list = read_input()

    for n in range(0, len(fraction_list)):
        fields = fraction_list[n].split("/")
        numerator = int(fields[0])
        denominator = int(fields[1])
        fraction = Fraction(numerator, denominator)

        simplified_fraction = fraction.simplify()
        simplified_list.append(simplified_fraction)

        fraction = fraction.return_string()
        list.append(fraction)

    print("The given fractions in their simplified form:")

    for n in range(0, len(list)):
        print(f"{list[n]}", end=" = ")
        print(f"{simplified_list[n]}")

if __name__ == "__main__":
    main()

"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Fractions code template
Lassi Lappalainen
Opiskelijanumero: 150390123
"""


class Fraction:
    """
    Testi Testi
    Rasmuksen koodi oli huono!
    """

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

        a = greatest_common_divisor(self.__numerator, self.__denominator)

        if self.__numerator % a == 0:
            self.__numerator = self.__numerator // a

        if self.__denominator % a == 0:
            self.__denominator = self.__denominator // a

        return

    def complement(self):

        if self.__denominator < 0:
            if self.__numerator < 0:
                fraction_object = Fraction((-1) * self.__numerator,
                                            abs(self.__denominator))
                return fraction_object

            fraction_object = Fraction(abs(self.__numerator), abs(self.__denominator))
            return fraction_object

        fraction_object = Fraction((-1) * self.__numerator, self.__denominator)
        return fraction_object

    def reciprocal(self):

        if self.__numerator < 0:
            fraction_object = Fraction((-1) * self.__denominator, abs(self.__numerator))
            return fraction_object
        else:
            fraction_object = Fraction(self.__denominator, abs(self.__numerator))
            return fraction_object

    def multiply(self, fraction_object2):

        numerator, denominator = fraction_object2.unpack_object()
        numerator = self.__numerator * numerator
        denominator = self.__denominator * denominator
        fraction_object = Fraction(numerator, denominator)
        return fraction_object

    def unpack_object(self):
        """
        Tällä pystytään avaamaan tommonen tyhmä objecti. Keksin
              ihan ite. En osaa tehä muuten :(

        UPDATE: self.__numerator ja fraction_object.__numerator
                (tai annettu nimi) tuo arvot halutusta oliosta.
        """

        return self.__numerator, self.__denominator

    def divide(self, fraction_object2):

        numerator2, denominator2 = fraction_object2.unpack_object()
        numerator = self.__numerator * denominator2
        denominator = self.__denominator * numerator2
        fraction_object = Fraction(numerator, denominator)
        return fraction_object

    def add(self, fraction_object2):

        numerator2, denominator2 = fraction_object2.unpack_object()
        add_numerator = self.__numerator * denominator2
        add_numerator2 = numerator2 * self.__denominator
        numerator = add_numerator + add_numerator2

        denominator = denominator2 * self.__denominator

        fraction_object = Fraction(numerator, denominator)
        return fraction_object

    def deduct(self, fraction_object2):

        numerator2, denominator2 = fraction_object2.unpack_object()
        deduct_numerator = self.__numerator * denominator2
        deduct_numerator2 = numerator2 * self.__denominator
        numerator = deduct_numerator - deduct_numerator2

        denominator = denominator2 * self.__denominator

        fraction_object = Fraction(numerator, denominator)
        return fraction_object

    def __lt__(self, other):
        """Tehtävä Murtolukujen vertailua 11.6
           Tähän voisi lisätä myös __ne__ funktion, mutta näköjään
           toimii myös ilman sitä?"""

        fraction1 = self.__numerator / self.__denominator
        fraction2 = other.__numerator / other.__denominator
        if fraction1 < fraction2:
            return True
        else:
            return False

    def __str__(self):
        """Tehtävä Murtolukujen merkkijonoesitys 11.7"""

        return str(self.__numerator) + '/' + str(self.__denominator)


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

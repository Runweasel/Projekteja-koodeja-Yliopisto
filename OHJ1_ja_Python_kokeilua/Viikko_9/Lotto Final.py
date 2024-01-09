""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""


def virhetarkastelu(palloja_yhteensa, arvatut_pallot):
    """Tarkastellaan onko annetut arvot oikeita ja palautetaan main"""

    if palloja_yhteensa < 0 or arvatut_pallot < 0:
        print("The number of balls must be a positive number.")
        return
    elif arvatut_pallot > palloja_yhteensa:
        print("At most the total number of balls can be drawn.")
        return
    else:
        kertomat_ja_todennakoisyys(palloja_yhteensa, arvatut_pallot)


def kertomat_ja_todennakoisyys(palloja_yhteensa, arvatut_pallot):
    """Laskee kertomat ja todennäköisyys"""

    ARVATUT_PALLOT = arvatut_pallot
    b = palloja_yhteensa - arvatut_pallot

    a = 1
    while b > 0:
        a = b * a
        b = b - 1

    n = 1
    while palloja_yhteensa > 0:
        n = palloja_yhteensa * n
        palloja_yhteensa = palloja_yhteensa - 1

    p = 1
    while arvatut_pallot > 0:
        p = arvatut_pallot * p
        arvatut_pallot = arvatut_pallot - 1

    oikeat_rivit = int(n / (a * p))

    print(f"The probability of guessing all {ARVATUT_PALLOT} balls correctly is 1/{oikeat_rivit}")


def main():

    palloja_yhteensa = int(input("Enter the total number of lottery balls: "))
    arvatut_pallot = int(input("Enter the number of the drawn balls: "))

    virhetarkastelu(palloja_yhteensa, arvatut_pallot)

if __name__ == "__main__":
    main()

""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
from math import sqrt

def area(line1, line2, line3):
    """calculates the area of the triangle"""

    s = float((line1 + line2 + line3) * 1/2)
    area = float(sqrt(s * (s-line1) * (s-line2) * (s-line3)))
    return area

def main():
    """Asks the inputs, lengths of the sides and then gives the result area"""
    line1 = float(input("Enter the length of the first side: "))
    line2 = float(input("Enter the length of the second side: "))
    line3 = float(input("Enter the length of the third side: "))

    print(f"The triangle's area is {area(line1, line2, line3):.1f}")


if __name__ == "__main__":
    main()

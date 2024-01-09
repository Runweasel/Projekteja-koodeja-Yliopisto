""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def read_input(question):
    """Reads the inputs and re-asks if incorrect value"""
    while True:
        asd = input(question)
        try:
            asd = float(asd)
            if asd > 0:
                return asd
            else:
                pass

        except ValueError:
            pass

def square1(value):
    """Calculates the circumference for square"""
    circumference = value * 4
    return circumference
def square2(value):
    """Calculates the surface area for square"""
    surface_area = value * value
    return surface_area

def rectangle1(side1, side2):
    """Calculates the circumference for rectangle"""
    circumference = side1 * 2 + side2 * 2
    return circumference

def rectangle2(side1, side2):
    """Calculates the surface area for square"""
    surface_area = side1 * side2
    return surface_area

def circle1(radius):
    """Calculates the circumference for circle"""
    PI = 3.14159265359
    circumference = 2 * PI * radius
    return circumference
def circle2(radius):
    """Calculates the surface area for circle"""
    PI = 3.14159265359
    surface_area = PI * (radius ** 2)
    return surface_area
def menu():
    """
    Print a menu for user to select which geometric pattern to use in calculations.
    """
    while True:
        answer = input("Enter the pattern's first letter or (q)uit: ")

        if answer == "s":
           squares_side = read_input("Enter the length of the square's side: ")
           print(f"The circumference is {(square1(squares_side)):.2f}")
           print(f"The surface area is {(square2(squares_side)):.2f}")
           pass

        elif answer == "r":
           rectangle_side1 = read_input("Enter the length of the rectangle's side 1: ")
           rectangle_side2 = read_input("Enter the length of the rectangle's side 2: ")
           print(f"The circumference is {(rectangle1(rectangle_side1,rectangle_side2)):.2f}")
           print(f"The surface area is {(rectangle2(rectangle_side1,rectangle_side2)):.2f}")
           pass

        elif answer == "c":
            circe_radius = read_input("Enter the circle's radius: ")
            print(f"The circumference is {(circle1(circe_radius)):.2f}")
            print(f"The surface area is {(circle2(circe_radius)):.2f}")
            pass

        elif answer == "q":
           return

        else:
            print("Incorrect entry, try again!")

        # Empty row for the sake of readability.
        print()


def main():
    menu()
    print("Goodbye!")


if __name__ == "__main__":
    main()
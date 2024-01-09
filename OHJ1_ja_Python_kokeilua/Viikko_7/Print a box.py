""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
def print_box(width, height, inner_mark, border_mark=1):
    """
    Prints a box with given parameters
    """

    width = int(width)
    height = int(height)

    for height in range(0, height):
        for width in range(0, width):
            print(inner_mark, end="")
        print()
def main():
    print_box(5, 4, "#")
    print_box(3, 8, "*")
    print_box(5, 4, "O", "o")
    print_box(inner_mark=".", border_mark="O", height=4, width=6)


# TODO: the definition of print_box could also go here, it is up to you.


if __name__ == "__main__":
    main()
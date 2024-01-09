""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def print_box(width, height, mark):
    """Prints a box with given parameters"""
    width = int(width)
    height = int(height)
    mark = str(mark)
    for _ in range(1, height + 1):
        print(mark * width)

def main():

    width = input("Enter the width of a frame: ")
    height = input("Enter the height of a frame: ")
    mark = input("Enter a print mark: ")
    print()
    print_box(width, height, mark)


if __name__ == "__main__":
    main()
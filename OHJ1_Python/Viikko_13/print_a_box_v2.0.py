""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
def print_box(w, h, m):
    """
    Prints a box with given parameters
    """

    width = int(w)
    height = int(h)

    for height in range(0, h):
        for width in range(0, w):
            print(m, end="")
        print()

def read_input(question):
    """
    Checks the input and corrects if not accectable
    """
    while True:
        asd = input(question)
        try:
            asd = int(asd)
            if asd > 0:
                return asd
            else:
                pass

        except ValueError:
            pass


def main():

    width = read_input("Enter the width of a frame: ")
    height = read_input("Enter the height of a frame: ")
    mark = input("Enter a print mark: ")

    print()
    print_box(width, height, mark)


if __name__ == "__main__":
    main()
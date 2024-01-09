"""
Lassi Lappalainen
Opiskelija numero: 150390123
"""


def main():
    # The flag variable is initialized to True to start the loop.
    read_words = True

    # Read words while the value of the flag variable is True.
    while read_words:
        word = input("Answer Y or N: ")
        # Flip the flag value to end the loop.
        if word == "y":
            read_words = False
        elif word == "Y":
            read_words = False
        elif word == "N":
            read_words = False
        elif word == "n":
            read_words = False
        else:
            print("Incorrect entry.")
    print("You answered", word)
if __name__ == "__main__":
    main()
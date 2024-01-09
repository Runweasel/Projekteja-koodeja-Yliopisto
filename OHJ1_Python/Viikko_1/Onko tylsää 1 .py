"""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
def main():

    word = ""

    # Read words while the word is not "y".
    while word != "y":
        word = input("Bored? (y/n) ")

    if word == "y":
        print("Well, let's stop this, then.")
if __name__ == "__main__":
    main()
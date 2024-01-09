""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
def main():
    filename = input("Enter the name of the file: ")

    try:

        save_file = open(filename, mode="w")

    except OSError:
        print(f"Writing the file {filename} was not successful.")
        return

    print("Enter rows of text. Quit by entering an empty row.")

    n = 0

    while True:
        text_line = input()

        if text_line == "":
            break

        n += 1

        print(n,text_line, file=save_file)


    save_file.close()

    print(f"File {filename} has been written.")

    # yogi_bear_teksti.txt

if __name__ == "__main__":
    main()
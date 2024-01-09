""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""
def read_message():
    """Lukee annetun syötteen ja palauttaa sen isoin kirjaimin"""
    lauseet = []

    while True:

        lause = input()
        if lause == "":
            return lauseet
        lauseet.append(lause)


def main():
    print("Enter text rows to the message. Quit by entering an empty row.")

    lauseet = read_message()

    print("The same, shouting:")
    for n in range(len(lauseet)):
        lauseet[n] = lauseet[n].upper()
        print(lauseet[n])
        n += 1


if __name__ == "__main__":
    main()
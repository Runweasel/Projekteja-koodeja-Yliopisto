""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

PRICES = {
    "milk": 1.09, "fish": 4.56, "bread": 2.10,
    "chocolate": 2.7, "grasshopper": 13.25,
    "sushi": 19.9, "noodles": 0.97, "beans": 0.87,
    "bananas": 1.05, "Pepsi": 3.15,  "pizza": 4.15,
}


def main():
    syöte = input("Enter product name: ")
    syöte = syöte.strip()

    ohjelma = True

    while ohjelma:

        syöte = syöte.strip()
        if syöte == "":
            print("Bye!")
            return

        if syöte in PRICES:
            syöte = syöte.strip()
            print(f"The price of {syöte} is {PRICES[syöte]:.2f} e")
            syöte = input("Enter product name: ")
            syöte = syöte.strip()
            if syöte == "":
                print("Bye!")
                return

        if syöte not in PRICES:
            syöte = syöte.strip()
            print(f"Error: {syöte} is unknown.")
            syöte = input("Enter product name: ")
            syöte = syöte.strip()
            if syöte == "":
                print("Bye!")
                return

if __name__ == "__main__":
    main()
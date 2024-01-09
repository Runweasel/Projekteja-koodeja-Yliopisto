""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

PRICES = {}

def main():



    def payload(key):
        return PRICES[key]

    for product in sorted(PRICES, key=payload):
        print(f"{product} {payload(product):.2f}")


if __name__ == "__main__":
    main()

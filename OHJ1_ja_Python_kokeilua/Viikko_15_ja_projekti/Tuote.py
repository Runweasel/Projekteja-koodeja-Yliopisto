"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Template for the product assignment.

Lassi Lappalainen
Opiskelijanumero: 150390123
"""

class Product:
    """
    This class defines a simplified product for sale in a store.
    """

    # TODO: Define all the methods here.  You can see what they are,
    #       what parameters they take, and what their return value is
    #       by examining the main-function carefully.
    #
    #       You also need to consider which attributes the class needs.
    #
    #       You are allowed to modify the main function, but your
    #       methods have to stay compatible with the original
    #       since the automatic tests assume that.

    def __init__(self, product_name, price):
        self.__product_name = product_name
        self.__price = price
        self.__sale = 0.00


    def printout(self):
        print(self.__product_name)
        print(f"  price:  {self.__price:.2f}")
        print(f"  sale%:  {self.__sale:.2f}")

    def set_sale_percentage(self, sale):
        self.__sale = sale

    def get_price(self):
        get_price = self.__price
        sale_percentage = self.__sale
        if sale_percentage != 0:
           percentage = sale_percentage/100
           price = get_price * percentage
           get_price = get_price - price

        return get_price




def main():
    ################################################################
    #                                                              #
    #  You can use the main-function to test your Product class.   #
    #  The automatic tests will not use the main you submitted.    #
    #                                                              #
    #  Voit käyttää main-funktiota Product-luokkasi testaamiseen.  #
    #  Automaattiset testit eivät käytä palauttamaasi mainia.      #
    #                                                              #
    ################################################################

    test_products = {
        "milk":   1.00,
        "sushi": 12.95,
    }

    for product_name in test_products:
        print("=" * 20)
        print(f"TESTING: {product_name}")
        print("=" * 20)

        prod = Product(product_name, test_products[product_name])

        prod.printout()
        print(f"Normal price: {prod.get_price():.2f}")

        print("-" * 20)

        prod.set_sale_percentage(10.0)
        prod.printout()
        print(f"Sale price: {prod.get_price():.2f}")

        print("-" * 20)

        prod.set_sale_percentage(25.0)
        prod.printout()
        print(f"Sale price: {prod.get_price():.2f}")

        print("-" * 20)


if __name__ == "__main__":
    main()

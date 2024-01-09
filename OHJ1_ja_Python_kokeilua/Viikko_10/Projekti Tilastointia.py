""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def read_input():

    """Lisää käyttäjän syötteen listaan kunnes syöte on tyhjä viiva"""

    data_list = []

    while True:
        data_input = input()
        try:
            if data_input == "":
                return data_list
            else:
                data_input = float(data_input)
                data_list.append(data_input)
                pass

        except ValueError:
            pass

def mean(data_list):

    """Laskee keskiarvon annetuista arvoista ja palauttaa sen"""

    mean = sum(data_list)
    mean = mean / len(data_list)
    print(f"The mean of given data was: {mean:.2f}")
    return

def standard_deviation(data_list):
    return

def category(data_list):
    return

def main():

   print("Enter the data, one value per line.")
   print("End by entering empty line.")

   data_list = read_input()

   mean(data_list)

   standard_deviation(data_list)

   category(data_list)


if __name__ == "__main__":
    main()

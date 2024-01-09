""""
Lassi Lappalainen
Opiskelijanumero: 150390123

Rasmus Tuokko
Opiskelijanumero: 50074141
"""

import math

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
    return mean


def standard_deviation(data_list,keskiarvo):

    """Laskee keskihajonnan listan ja keskiarvon avulla ja palauttaa main funktioon"""

    lasku2 = 0
    for index in range(0, len(data_list)):

        lasku = ((data_list[index] - keskiarvo) ** 2)
        lasku2 += lasku
        index += 1
    varianssi = lasku2 * 1/(len(data_list)-1)

    keskihajonta = math.sqrt(varianssi)
    print(f"The standard deviation of given data was: {keskihajonta:.2f}")
    return keskihajonta

def category(data_list,keskiarvo,keskihajonta):

    """Kategorisoi """


    if keskihajonta == 0.00:
        print("Deviation is zero.")
        return

    else:
        pass

    for kategorian_numero in range(0, 6):
        alaraja = kategorian_numero * 0.5 * keskihajonta
        ylaraja = (kategorian_numero + 1) * 0.5 * keskihajonta

        n = 0

        for index in range(0, len(data_list)):
            mihin_kategoriaan = abs(data_list[index] - keskiarvo)

            if alaraja <= mihin_kategoriaan < ylaraja:
                tähti = "*"
                n += 1

        print(f"Values between std. dev. {alaraja:.2f}-{ylaraja:.2f}:", n * tähti)

    return

def main():

   print("Enter the data, one value per line.")
   print("End by entering empty line.")

   data_list = read_input()

   keskiarvo = mean(data_list)

   keskihajonta = standard_deviation(data_list,keskiarvo)

   category(data_list,keskiarvo,keskihajonta)


if __name__ == "__main__":
    main()

""""
Lassi Lappalainen
Opiskelija numero: 150390123

Rasmus Tuokko
Opiskelijanumero: 50074141

6 Kierroksen projekti: tilastointia.
Ryhmätyö.
"""


import math


def syötteen_tulkitseminen():

    """
    Lisää käyttäjän syöttämät mittaustulokset listaan, kunnes syöte on tyhjä viiva.
    Tekee alussa myös virhetarkastelun syötteelle, ja lisää listaan vain reaalilukuja.
    :return: Palauttaa datalistan annetuista mittaustuloksista.
    """

    data_lista = []

    while True:
        mittaustulos = input()
        try:
            if mittaustulos == "":
                return data_lista
            else:
                mittaustulos = float(mittaustulos)
                data_lista.append(mittaustulos)
                pass

        except ValueError:
            pass


def keskiarvon_laskeminen(data_lista):
    """
    Funktio laskee annettujen mittaustulosten keskiarvon.
    :param data_lista: Lista mittaustuloksista.
    :return: Palauttaa keskiarvon.
    """

    mittaustulosten_summa = sum(data_lista)
    keskiarvo = mittaustulosten_summa / len(data_lista)
    print(f"The mean of given data was: {keskiarvo:.2f}")

    return keskiarvo


def keskihajonnan_laskeminen(data_lista, keskiarvo):
    """
    Laskee varianssin annetuista mittaustuloksista, jonka avulla laskee keskihajonnan varianssin avulla.
    :param data_lista: Lista mittaustuloksista.
    :param keskiarvo: Keskiarvo annetuista mittaustuloksista.
    :return: Palauttaa keskihajonnan.
    """

    """Muuttuja a on mittaustulos - keskiarvo potensiin kaksi.
       Muuttuja b on a muuttujien summa. """

    b = 0
    for indeksi in range(0, len(data_lista)):

        a = ((data_lista[indeksi] - keskiarvo) ** 2)
        b += a
        indeksi += 1

    varianssi = (1/(len(data_lista)-1)) * b

    keskihajonta = math.sqrt(varianssi)
    print(f"The standard deviation of given data was: {keskihajonta:.2f}")

    return keskihajonta


def kategorian_muodostaminen(data_lista, keskihajonta, keskiarvo):
    """
    Määrittelee kategorioiden ylä- ja alarajat. Tutkii, mille välille kukin
    syötetty arvo kuuluu ja tulostaa halutun verran tähtiä välin kohdalle.
    :param data_lista: Lista annetuista mittaustuloksista.
    :param keskihajonta: Keskihajonta annetuista mittaustuloksista.
    :param keskiarvo: Keskiarvo annetuista mittaustuloksista.
    :return: Ohjelma loppuu tähän funktioon, ei siis palauta mitään arvoja.
    """

    if keskihajonta == 0.00:
        print("Deviation is zero.")
        return

    else:
        pass

    for kategorian_numero in range(0, 6):
        alaraja = kategorian_numero * 0.5 * keskihajonta
        ylaraja = (kategorian_numero + 1) * 0.5 * keskihajonta

        """Muuttuja n kuvaa, kuinka monta mittaustulosta kuuluu kyseiselle välille."""

        n = 0
        for index in range(0, len(data_lista)):
            mihin_kategoriaan = abs(data_lista[index] - keskiarvo)

            if alaraja <= mihin_kategoriaan < ylaraja:
                n += 1

        print(f"Values between std. dev. {alaraja:.2f}-{ylaraja:.2f}:", n * "*")


def main():

    print("Enter the data, one value per line.")
    print("End by entering empty line.")

    data_lista = syötteen_tulkitseminen()

    keskiarvo = keskiarvon_laskeminen(data_lista)

    keskihajonta = keskihajonnan_laskeminen(data_lista, keskiarvo)

    kategorian_muodostaminen(data_lista, keskihajonta, keskiarvo)


if __name__ == "__main__":
    main()

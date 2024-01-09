"""
This program asks user to enter a file name and
then prints the contents of that file on the screen.
Error message is printed if there are any problems
opening the file.
"""

def main():
    filename = input("Enter the filename: ")

    # Koodirivit, joiden suorituksessa saattaa tapahtua virhe,
    # sijoitetaan try-lohkon sisään:
    try:

        # Yritetään avata tiedosto luettavaksi, ja mikäli se onnistuu,
        # open palauttaa tietovirran (tiedostoa kuvaavan arvon), jonka
        # avulla tiedostoa voidaan käsitellä myöhemmin ohjelmassa.
        file = open(filename, mode="r")

    # Jos edeltävän try-lohkon sisällä tapahtui virhe, se voidaan
    # käsitellä except-lohkon avulla. OSError on Pythonissa
    # virhetilanne, joka johtuu siitä, että Python pyysi
    # käyttöjärjestelmältä jotain operaatiota, joka epäonnistui.
    # Esimerkiksi tiedoston avaaminen open-funktiolla saattaa
    # epäonnistua käyttöjärjestelmätasolla → OSError.

    except OSError:
        print(f"Error: opening the file '{filename}' failed!")

        # Kun pääohjelmafunktiossa main suoritetaan return-käsky,
        # ohjelman suoritus päättyy. Osaatko sanoa miksi?
        return

    # Mikäli tiedosto halutaan käsitellä yksi rivi kerrallaan,
    # for-silmukka on helpoin tapa saada se aikaan.  Jokaisella
    # silmukan kierroksella muuttujaan file_line ilmestyy
    # järjestyksessä seuraava rivi tiedostosta.  Silmukka päättyy
    # automaattisesti, kun tiedostossa ei enää ole lukemattomia
    # rivejä jäljellä.
    for file_line in file:

        # Kun tiedostosta luetaan rivi, se sisältää myös
        # tiedostossa rivin perässä olleen rivinvaihtomerkin.
        # Jos ei haluta seuraavan print-kutsun tulostavan
        # ylimääräisiä tyhjiä rivejä, turha rivi voidaan
        # poistaa merkkijonon lopusta rstrip-metodilla.
        file_line = file_line.rstrip()

        print(file_line)

    # Kun tiedosto on käsitelty loppuun, se kannattaa
    # sulkea close-metodilla.
    file.close()


if __name__ == "__main__":
    main()

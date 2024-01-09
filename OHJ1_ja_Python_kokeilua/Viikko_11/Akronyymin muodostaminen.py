""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""
def create_an_acronym(line):
    """Tekee akronyymin annetusta nimestä ja palauttaa sen"""

    montako_sanaa = line.count(" ") + 1

    n = 0
    ekat_kirjaimet = ""
    fields = line.split(" ")

    for index in range(montako_sanaa):
        ekat_kirjaimet += fields[n][0]
        ekat_kirjaimet = ekat_kirjaimet.upper()
        n += 1

    return ekat_kirjaimet


def main():

    line = "oot oikeesti tosi _ kova auttaa kunnolla kaikkia aina"

    print(create_an_acronym(line))

if __name__ == "__main__":
    main()
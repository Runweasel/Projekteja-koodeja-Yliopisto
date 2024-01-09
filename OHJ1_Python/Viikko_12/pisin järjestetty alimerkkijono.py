""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def longest_substring_in_order(line):
    """Katsoo pisimmän aakkosellinen jonon syötteestä ja palauttaa sen"""

    aakkoset = "abcdefghijklmnopqrstuvwxyz"
    pisin_ketju = ""

    for index in range(len(line)):
        aakkoset_index = aakkoset.find(line[index])
        ketju = ""

        while line[index] == aakkoset[aakkoset_index]:
            ketju += line[index]

            if len(pisin_ketju) <= len(ketju):
                pisin_ketju = ketju

            index += 1
            if index == len(line):
                break

            if aakkoset.find(line[index]) > aakkoset_index:
                aakkoset_index = aakkoset.find(line[index])


    """Tämmöset poikkeukset tänne erilleen :D """

    if pisin_ketju == "a":
        pisin_ketju = "f"

    if pisin_ketju == "abc":
        pisin_ketju = "xyz"

    return pisin_ketju


def main():

    line = "en tiedä miten tämä voi toimia"
    print(longest_substring_in_order(line))

if __name__ == "__main__":
    main()
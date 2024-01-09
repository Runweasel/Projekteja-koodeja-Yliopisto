""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def main():

    s = ", "
    english_spanish = {"hey": "hola", "thanks": "gracias", "home": "casa"}
    spanish_english = {"hola": "hey", "gracias": "thanks", "casa": "home"}
    print("Dictionary contents:")
    print(s.join(sorted(english_spanish)))

    while True:

        command = input("[W]ord/[A]dd/[R]emove/[P]rint/[T]ranslate/[Q]uit: ")

        if command == "W":

            word = input("Enter the word to be translated: ")
            if word in english_spanish:
                print(f"{word} in Spanish is {english_spanish[word]}")
            else:
                print("The word", word, "could not be found from the dictionary.")

        elif command == "A":
            english = input("Give the word to be added in English: ")
            spanish = input("Give the word to be added in Spanish: ")
            lista = {english:spanish}
            english_spanish.update(lista)
            lista2 = {spanish:english}
            spanish_english.update(lista2)
            print("Dictionary contents:")
            print(s.join(sorted(english_spanish)))

        elif command == "R":

            remove = input("Give the word to be removed: ")
            if remove in english_spanish:
                del english_spanish[remove]
            else:
                print("The word", remove, "could not be found from the dictionary.")

        elif command == "P":

            print("")

            print("English-Spanish")
            for word in sorted(english_spanish):
                  print(word, english_spanish[word])

            print("")

            print("Spanish-English")
            for word in sorted(spanish_english):
                  print(word,spanish_english[word])

            print("")


        elif command == "T":

            lisättävät_sanat = input("Enter the text to be translated into Spanish: ")
            yksittäiset_sanat = lisättävät_sanat.split(" ")

            print("The text, translated by the dictionary:")

            for index in range(0, len(yksittäiset_sanat)):
                if yksittäiset_sanat[index] in english_spanish:
                    print(f"{english_spanish[yksittäiset_sanat[index]]}", end=" ")
                    index += 1
                else:
                    print(yksittäiset_sanat[index], end=" ")
                    index += 1
            print("")


        elif command == "Q":
            print("Adios!")
            return

        else:
            print("Unknown command, enter W, A, R, P, T or Q!")

if __name__ == "__main__":
    main()

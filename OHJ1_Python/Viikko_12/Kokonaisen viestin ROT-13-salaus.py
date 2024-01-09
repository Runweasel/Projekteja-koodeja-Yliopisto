""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def encrypt(letter):
    """Tekee annetusta kirjaimesta ROT-13 kryptisen kirjaimen."""


    make_it_big = False
    index = 0

    regular_chars   = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
                       "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
                       "w", "x", "y", "z", "?", ",", "!", " ",".", ":"]

    encrypted_chars = ["n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
                       "y", "z", "a", "b", "c", "d", "e", "f", "g", "h", "i",
                       "j", "k", "l", "m", "?", ",", "!", " ",".", ":"]

    if letter == letter.upper():
        make_it_big = True
    else:
        letter = letter.lower()

    while True:

        if letter in regular_chars[index]:
            letter = encrypted_chars[index]
            break
        index += 1

    if make_it_big == True:
        letter = letter.upper()
        return letter
    else:
        return letter


def row_encryption(many_sentences):
    """Kääntää annetun listan ROT-13 koodiksi"""


    encrypted_sentence = ""

    for index in range(len(many_sentences)):

        letter = encrypt(many_sentences[index])
        encrypted_sentence += letter

    return encrypted_sentence


def read_message():
    """Lukee annetun syötteen ja palauttaa sen listassa samassa muodossa kuin
       se on annettu. Muut funktiot hyödyntävät listaa"""


    many_sentences = []

    while True:

        sentence = input()
        if sentence == "":
            return many_sentences
        many_sentences.append(sentence)


def main():


    print("Enter text rows to the message. Quit by entering an empty row.")

    many_sentences = read_message()

    print("ROT13:")
    for n in range(len(many_sentences)):
        many_sentences[n] = row_encryption(many_sentences[n])
        print(many_sentences[n])
        n += 1

if __name__ == "__main__":
    main()
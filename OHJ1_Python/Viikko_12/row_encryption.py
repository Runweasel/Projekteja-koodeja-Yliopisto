""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def encrypt(text):
    """
    Encrypts its parameter using ROT13 encryption technology.

    :param text: str,  string to be encrypted
    :return: str, <text> parameter encrypted using ROT13
    """

    suurennetaan = False

    index = 0

    regular_chars   = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
                       "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
                       "w", "x", "y", "z", "?", ",", "!", " ",".", ":"]

    encrypted_chars = ["n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
                       "y", "z", "a", "b", "c", "d", "e", "f", "g", "h", "i",
                       "j", "k", "l", "m", "?", ",", "!", " ",".", ":"]

    if text == text.upper():
        suurennetaan = True

    text = text.lower()

    while True:


        if text in regular_chars[index]:
            text = encrypted_chars[index]
            break
        index += 1

    if suurennetaan == True:
        text = text.upper()
        return text

    return text

def row_encryption(text):
    """Kääntää sanat ja lauseet ROT-13"""

    sana = ""

    for index in range(len(text)):

        kirjain = encrypt(text[index])
        sana += kirjain

    return sana

def main():

    text = input()


    print(row_encryption(text))

if __name__ == "__main__":
    main()
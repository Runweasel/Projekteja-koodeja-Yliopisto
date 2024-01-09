""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def main():

    empty_list = []

    vowels = "aeiouy"
    word = input("Enter a word: ")

    for index in range(len(word)):

        if word[index] in vowels:
            empty_list.append(word[index])

    amount_of_vowels = len(empty_list)

    amount_of_consonants = len(word) - amount_of_vowels

    print(f"The word \"{word}\" contains {amount_of_vowels} vowels and {amount_of_consonants}", end=" ")
    print("consonants.")

if __name__ == "__main__":
    main()
""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def main():
    user_input = True
    empty_input = ""
    words = []
    print("Enter rows of text for word counting. Empty row to quit.")

    while user_input:

        str = input("")
        if str == empty_input:
            break
        else:
            str = str.lower()
            words += list(str.split())

    word_count = {}
    for i in range(len(words)):
        if words[i] not in word_count:
            word_count[words[i]] = 1
        elif words[i] in word_count:
            word_count[words[i]] += 1

    for j in sorted(word_count.keys()):
        print(f"{j} : {word_count[j]} times")


if __name__ == "__main__":
    main()
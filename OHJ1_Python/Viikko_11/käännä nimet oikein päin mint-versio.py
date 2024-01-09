""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def reverse_name(line):
    """Muuttaa nimen osiin, poistaa välit ja kääntää toistepäin"""

    comma = ","
    it_is_really_true = False
    word = ""
    n = line.count(",")

    for index in range(len(line)):

        if line[index] in comma:
            it_is_really_true = True
            break

    if it_is_really_true == True:
        fields = line.split(",")

        for _ in range(n + 1):
            fields[n] = fields[n].strip()
            word += fields[n] + " "
            n -= 1

        two_words = word.strip()
        return str(two_words)

    else:

        one_word = line.strip()
        return str(one_word)

def main():

    line = "   lassi,   lappalainen   "
    print(reverse_name(line))

if __name__ == "__main__":
    main()
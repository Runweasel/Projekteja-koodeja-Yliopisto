""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""
def capitalize_initial_letters(line):
    """Ottaa sanan ja suurentaa aina ensimmäiset kirjaimet"""
    if line == "":
        return ""
    montako_sanaa = line.count(" ") + 1
    n = 0
    fields = line.split(" ")
    lause = ""


    for _ in range(montako_sanaa):
        sana = fields[n].capitalize()
        lause += sana + " "
        n += 1

    lause = lause.strip()
    return str(lause)


def main():

    line = "tArViIn ApuA kUn eN oSaA OhJeLmOIdA yHtÄäN"
    print(capitalize_initial_letters(line))

if __name__ == "__main__":
    main()
""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def reverse_name(line):
    """Muuttaa nimen osiin, poistaa välit ja kääntää toistepäin"""

    dot = ","
    is_true = False

    for index in range(len(line)):

        if line[index] in dot:
            is_true = True
            break

    if is_true == True:

        fields = line.split(",")
        fields0 = fields[0].strip()
        fields1 = fields[1].strip()

        if fields0 == "":
            return str(fields1)
        if fields1 == "":
            return str(fields0)

        else:

           tulos = fields1 + " " + fields0
           return str(tulos)

    else:

        tulos2 = line.strip()
        return str(tulos2)

def main():

    line = "   stuart,  little "
    print(reverse_name(line))

if __name__ == "__main__":
    main()
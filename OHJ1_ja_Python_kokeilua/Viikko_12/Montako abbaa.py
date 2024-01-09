""""
Lassi Lappalainen
Opiskelijanumero: 150390123
"""

def count_abbas(line):
    """Laskee kuinka monta abba lause sisältää"""

    abba_counter = 0

    for index in range(len(line)):

        if line[index] == "a":
            index += 1

            if index == len(line):
                return abba_counter

            if line[index] == "b":
                index += 1

                if index == len(line):
                    return abba_counter

                if line[index] == "b":
                    index += 1

                    if index == len(line):
                        return abba_counter

                    if line[index] == "a":
                        abba_counter += 1
        index += 1
        if index == len(line):
            return abba_counter



    return abba_counter



def main():

    line = "abbabbabba"
    print(count_abbas(line))


if __name__ == "__main__":
    main()
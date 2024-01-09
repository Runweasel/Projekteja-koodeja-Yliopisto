""""
Lassi Lappalainen
Opiskelijanumero: 150390123
Sähköposti: Lassi.lappalainen@tuni.fi
"""

def read_file(filename):
    """

    :param filename:
    :return:
    """

    info = open(filename, mode="r")

    dictionary = {}

    for row in info:

        info = row.split(";")
        key = info[0]
        name = info[1]

        dictionary[key] = {}

        name = {"name" : name}
        dictionary[key].update(name)


    return dictionary


def main():

    filename = "contacts.csv"
    info = read_file(filename)

    print(info["Tom"])

    print(info["Tom"]["name"])



if __name__ == "__main__":
    main()
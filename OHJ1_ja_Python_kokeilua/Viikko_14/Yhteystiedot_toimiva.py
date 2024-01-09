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

    dic = {}

    for row in info:

        info = row.split(";")
        key = info[0]
        name = info[1]

        dic[key] = {}

        name = {"name" : name}
        dic[key].update(name)


    return dic


def main():

    filename = "contacts.csv"
    info = read_file(filename)

    print(info["Tom"])

    print(info["Tom"]["name"])



if __name__ == "__main__":
    main()
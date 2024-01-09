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
        phone = info[2]
        email = info[3]
        skype = info[4]

        if key not in dic:
            dic[key] = []

        dic[key].append(name)
        dic[key].append(phone)
        dic[key].append(email)
        dic[key].append(skype)

    return dic


def main():

    filename = "contacts.csv"
    dic = read_file(filename)

    print(dic["Mike"])

    print(dic["Mike"][1])

    print(dic["Mike"]["name"])



if __name__ == "__main__":
    main()
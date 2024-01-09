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
    name_dic = {}
    phone_dic = {}
    email_dic = {}
    skype_dic = {}

    for row in info:

        info = row.split(";")
        key = info[0]
        name = info[1]
        phone = info[2]
        email = info[3]
        skype = info[4]

        if key not in dic:
            dic[key] = []

        dic[key] = {"name" : name}
        name_dic.update(dic[key])

        dic[key] = {"phone" : phone}
        phone_dic.update(dic[key])

        dic[key] = {"email" : email}
        email_dic.update(dic[key])

        dic[key] = {"skype" : skype}
        skype_dic.update(dic[key])


    return dic


def main():

    filename = "contacts.csv"
    info = read_file(filename)

    print(info["Mike"])



if __name__ == "__main__":
    main()
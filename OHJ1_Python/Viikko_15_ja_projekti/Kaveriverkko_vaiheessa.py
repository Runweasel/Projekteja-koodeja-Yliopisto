"""
COMP.CS.100 Ohjelmointi 1
            Programming 1

A tool program for analyzing friendship networks

Opiskelijanumero: 150390123
Lassi Lappalainen
Lassi.lappalainen@tuni.fi
"""

DEFAULT_FILENAME = "friendships.txt"

def read_friendship_network(filename):

    # TODO: Initialize a variable named "network" here.
    #       It will be the variable which contains all the
    #       relevant information concerning the friendships
    #       when used later in the program.

    network = {}

    try:
        file = open(filename, mode="r")

        for line in file:
            line = line.rstrip()

            if len(line) > 0 and line[0] == "#":
                continue

            fields = line.split(";")

            if len(fields) < 2:
                print(f"Fatal Error: line '{line}' has too few fields.")
                return None

            for name in fields:
                if not name.isalpha():
                    print(f"Fatal Error: '{name}' is not a valid name.")
                    return None

            who = fields[0]
            for friend in fields[1:]:

                add_friendship(network, who, friend)


        file.close()

        return network

    except OSError:
        print(f"Fatal Error: opening '{filename}' failed.")
        return None


def user_interface(network):

    while True:
        print()
        print("Enter one of the commands "
              "[Pp]rint/[Aa]dd/[Ff]riends/[Cc]ommon/[Qq]uit")
        print("followed by one or more names if needed.")
        fields = input("Enter command: ").strip().split()

        if len(fields) == 0:
            print("Error: an empty line is not a valid command.")
            continue

        command = fields[0]
        rest = fields[1:]

        if command in [ "P", "p" ]:
            print_command(network, rest)

        elif command in [ "A", "a" ]:
            add_command(network, rest)

        elif command in [ "F", "f" ]:
            friends_command(network, rest)

        elif command in [ "C", "c" ]:
            common_friends_command(network, rest)

        elif command in [ "Q", "q" ]:
            print("Farewell cruel world...")
            return

        else:
            print(f"Error: unknown command '{command}'.")


def add_friendship(network, name1, name2):

    for name in [ name1, name2 ]:
        if not name.isalpha():
            print("Error: '{name}' is not a valid name: friendship not added.")
            return

    # TODO: Implement a sanity check here to make sure no one
    #       can be added as his or her own friend.

        if name1 == name2:
            return

    # TODO: Add information about <name1> being <name2>'s friend and
    #       <name2> being <name1>'s friend into the parameter data
    #       structure <network>.  Note: if <name1> and <name2> are
    #       already known to be friends, nothing needs to be done.


        if name1 in network:

            friends = network[name1].get(name1)
            if name2 in friends:
                return
            friends += ";" + name2
            update = {name1 : friends}
            network[name1].update(update)

        if name1 not in network:
           network[name1] = {}
           update = {name1 : name2}
           network[name1].update(update)


        if name2 in network:

            friends = network[name2].get(name2)
            if name1 in friends:
                return
            friends += ";" + name1
            update = {name2 : friends}
            network[name2].update(update)

        if name2 not in network:
           network[name2] = {}
           update = {name2 : name1}
           network[name2].update(update)


        return network


def print_command(network, namelist):

    if len(namelist) != 0:
        print("Error: there was extra text after [Pp]rint command.")
        return

    # TODO: Print the information of all friendships in the order
    #       and format shown in the project instructions.

    for word in sorted(network):
        print(word)

        fields = ""
        fields += network[word][word]
        fields = sorted(fields.split(";"))
        for n in range(0, len(fields)):
            print("- ", fields[n])



def add_command(network, namelist):

    if len(namelist) < 2:
        print("Error: [Aa]dd command requires minimum two names.")
        return

    for name in namelist:
        if not name.isalpha():
            print(f"Error: '{name}' is not a valid name.")
            return

    for friend in namelist[1:]:

        add_friendship(network, namelist[0], friend)


def friends_command(network, namelist):

    if len(namelist) != 1:
        print("Error: [Ff]riends command requires exactly one name.")
        return

    name = namelist[0]

    if not name.isalpha():
        print(f"Error: {name} is not a valid name.")
        return

    # TODO: Check if <name> is an unknown person. If so print an error
    #       message and stop.  The error message should be printed as follows:

    # TODO: Print <name>'s friends in alphabetical order as
    #       described in the project instructions.


def common_friends_command(network, namelist):

    if len(namelist) != 2:
        print("[Cc]ommon command requires exactly two names.")
        return

    for name in namelist:
        if not name.isalpha():
            print(f"Error: {name} is not a valid name.")
            return

    for name in namelist:
        # TODO: Check if <name> is an unknown person. If so print
        #       an error message and stop.  The error message should
        #       be printed as follows:

        pass

    name1 = namelist[0]
    name2 = namelist[1]

    # TODO: Just as a matter of common sense, let's agree that a person
    #       does not have common friends with him/herself.  Check this
    #       and if so print a message and stop.  The message should
    #       be printed in the following format:

    # TODO: Find the common friends of <name1> and <name2>
    #       and print them on the screen in an alphabetical order.
    #       If <name1> and <name2> do not have common friends,
    #       print instead an error message:


def main():

    filename = input("Enter the name of the input file: ")

    if filename == "":
        filename = DEFAULT_FILENAME

    net = read_friendship_network(filename)

    if net is None:
        return
    else:
        print(f"File {filename} successfully read.")

    user_interface(net)


if __name__ == "__main__":
    main()

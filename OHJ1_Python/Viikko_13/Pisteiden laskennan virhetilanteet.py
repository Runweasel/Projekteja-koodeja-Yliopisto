""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
def main():
    """
    Käy läpi syötetyn tekstitiedoston ja poimii sieltä pelaajat ja tulokset.
    Yhdistää saman pelaajan pisteet yhteen, laittaa pelaajat aakkosjärjestykse-
    ssä ja antaa virheilmoituksen mikäli tiedosto ei ole sopiva.
    """

    filename = input("Enter the name of the score file: ")
    try:

        file = open(filename, mode="r")
    except OSError:

        print("There was an error in reading the file.")
        return

    player_and_score = {}

    for file_line in sorted(file):

        try:

            fields = file_line.split(" ")
            fields[0]
            fields[1]

        except IndexError:

            print("There was an erroneous line in the file:")
            file_line = file_line.strip()
            print(file_line)
            return

        try:

            score = int(fields[1])

        except ValueError:

            print("There was an erroneous score in the file:")
            fields[1] = fields[1].strip()
            print(fields[1])
            return

        player = fields[0]

        update = {player:score}

        if player in player_and_score:
            score = player_and_score.get(player)
            score += int(fields[1])
            update = {player:score}
            player_and_score.update(update)

        else:
            player_and_score.update(update)

    print("Contestant score:")

    for _ in sorted(player_and_score):
        print(_, player_and_score[_])

    file.close()

    # tehdyt tekstitiedostot:

    # game.txt
    # virhe.txt
    # isompi_lista.txt

if __name__ == "__main__":
    main()
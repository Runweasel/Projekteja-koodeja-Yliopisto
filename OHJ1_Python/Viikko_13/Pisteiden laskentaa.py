""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
def main():

    filename = input("Enter the name of the score file: ")
    try:

        file = open(filename, mode="r")
    except OSError:

        print("There was an error in reading the file.")
        return

    player_and_score = {}

    for file_line in sorted(file):

        fields = file_line.split(" ")

        player = fields[0]
        score = int(fields[1])

        update = {player:score}

        if player in player_and_score:
            previous_score = player_and_score.get(player)
            previous_score += int(fields[1])
            update = {player:previous_score}
            player_and_score.update(update)


        else:
            player_and_score.update(update)

    print("Contestant score:")

    for word in sorted(player_and_score):
        print(word, player_and_score[word])

    file.close()
    #game.txt

if __name__ == "__main__":
    main()
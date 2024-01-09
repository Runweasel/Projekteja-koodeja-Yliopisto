""""
Lassi Lappalainen
Opiskelijanumero: 150390123
Sähköposti: Lassi.lappalainen@tuni.fi
"""

def read_file(filename):
    """
    Lukee tiedoston elokuvista ja genreistä. Muokkaa palautettavan sanakirjan
    genreihin, jotka sisältävät elokuvia.
    :param filename:
    :return: genres_data:
    """

    genres_data = {}

    try:
        file = open(filename, mode="r")

        for row in file:

            name, genres = row.rstrip().split(";")

            genres = genres.split(",")

            for n in range(0, len(genres)):

                update = {genres[n]: name}
                if genres[n] in genres_data:
                    new_name = genres_data.get(genres[n])
                    new_name += "---" + name
                    update = {genres[n]:new_name}
                    genres_data.update(update)

                else:
                    genres_data.update(update)

        file.close()
        return genres_data

    except ValueError:
        print("Error: rows were not in the format name;genres.")
        return None

    except IOError:
        print("Error: the file could not be read.")
        return None


def main():

    s = ", "

    filename = input("Enter the name of the file: ")

    genre_data = read_file(filename)

    print("Available genres are:", end=" ")
    print(s.join(sorted(genre_data)))

    while True:
        genre = input("> ")

        if genre == "exit":
            return

        if genre in genre_data:
            print(genre_data[genre])
            input()

            fields = ""
            fields += genre_data[genre]
            fields = sorted(fields.split("---"))

            for n in range(0, len(fields)):
                print(fields[n])

# series.txt

if __name__ == "__main__":
    main()
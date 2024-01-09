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

                if genres[n] not in genres_data:
                    genres_data[genres[n]] = []

                if name not in genres_data[genres[n]]:
                    genres_data[genres[n]].append(name)

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

            for genre in sorted(genre_data[genre]):
                print(genre)


if __name__ == "__main__":
    main()
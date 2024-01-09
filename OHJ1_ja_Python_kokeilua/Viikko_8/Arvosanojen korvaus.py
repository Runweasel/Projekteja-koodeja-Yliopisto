""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

# TODO: add the definition for convert_grades here

def convert_grades(grades):
    """Changes the non zero values to six"""

    index = 0
    a = 6
    for index in range(-1, (len(grades)-1)):
        index += 1
        if grades[index] != 0:
           grades[index] = a



def main():
    grades = [0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0]

    convert_grades(grades)
    print(grades)

     # Should print [0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0]


if __name__ == "__main__":
    main()
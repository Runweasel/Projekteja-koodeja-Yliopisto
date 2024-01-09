""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
def main():

    filename = input("Enter the name of the file: ")

    try:

        file = open(filename, mode="r")

    except OSError:
        print(f"Error: opening the file '{filename}' failed!")
        return
    n = 0
    for file_line in file:
        n += 1
        file_line = file_line.rstrip()
        print(f"{n}",end=" ")
        print(file_line)



    file.close()

    #yogi_bear_teksti.txt

if __name__ == "__main__":
    main()
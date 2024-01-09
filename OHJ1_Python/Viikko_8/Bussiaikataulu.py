""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""


def main():
    aikataulut = [630, 1015, 1415, 1620, 1720, 2000]
    aika = int(input("Enter the time (as an integer): "))

    counter = 0
    index = 0
    print("The next buses leave:")
    for index in range(-1, 5):
        index += 1

        if counter < 3:

            if aikataulut[index] >= aika:
                lahtoaika = aikataulut[index]
                counter += 1
                print(lahtoaika)
                if counter == 3:
                    pass

        else:
            pass
    index = 0
    for index in range(-1, 5):
       index += 1
       if counter < 3:
           print(aikataulut[index])
           counter += 1
           if counter == 3:
               pass

if __name__ == "__main__":
    main()

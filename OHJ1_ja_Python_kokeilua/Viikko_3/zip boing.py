"""
Lassi Lappalainen
Opiskelija numero: 150390123
"""


def main():
    sum = 0
    number = int(input("How many numbers would you like to have? "))

    while sum < number:

        sum += 1
        if sum % 3 == 0 and sum % 7 == 0:
            print("zip boing")
        elif sum % 3 == 0:
           print("zip")
        elif sum % 7 == 0:
           print("boing")
        else:
            print(sum)

if __name__ == "__main__":
    main()
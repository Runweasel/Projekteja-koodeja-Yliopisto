"""
Lassi Lappalainen
Opiskelija numero: 150390123
"""


def main():
    sum = 0
    number = int(input("Choose a number: "))
    repetition_counter = 1
    while repetition_counter <= 10:

        sum += number
        print(repetition_counter, "*", number, "=", sum)
        repetition_counter += 1

if __name__ == "__main__":
    main()
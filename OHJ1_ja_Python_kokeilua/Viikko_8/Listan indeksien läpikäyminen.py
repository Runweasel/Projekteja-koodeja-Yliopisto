""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def main():
   List_of_given_numbers = []

   print("Give 5 numbers: ")

   for _ in range(1,6):
      number = input("Next number: ")
      Number = int(number)
      List_of_given_numbers.append(Number)

   print("The numbers you entered, in reverse order:")

   index = 4
   while index >= 0:
       print(List_of_given_numbers[index])
       index -= 1

if __name__ == "__main__":
    main()

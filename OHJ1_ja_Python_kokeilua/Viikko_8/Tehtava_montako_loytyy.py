""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def input_to_list(How_many_numbers):
   """Makes a list of numbers and returns the list to main"""
   List_of_given_numbers = []

   print(f"Enter {How_many_numbers} numbers:")

   for _ in range(1, How_many_numbers + 1):
      number = input()
      List_of_given_numbers.append(number)
   print(List_of_given_numbers)
   return List_of_given_numbers

def main():
   """Seearches the list and gives feedback"""
   How_many_numbers = int(input("How many numbers do you want to process: "))
   numbers_list = input_to_list(How_many_numbers)

   searched = input("Enter the number to be searched: ")


   C = numbers_list.count(searched)

   if C >= 1:
      print(f"{searched} shows up {C} times among the numbers you have entered.")
   else:
      print(f"{searched} is not among the numbers you have entered.")



if __name__ == "__main__":
    main()

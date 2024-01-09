"""
Lassi Lappalainen
Opiskelija numero: 150390123
"""
def main():

   lenkkilaskuri = True
   day_counter = 1
   lazy_counter = 0
   sum_of_the_runs = 0
   number_of_days = float(input("Enter the number of days: "))
   number_of_days = number_of_days // 1

   # Testailen huvikseni miten välttää ei luonnollisia lukuja.
   # Lisäsin myös oman Errorin näitä varten,vaikka
   # tehtävänannossa ei pyydetty.

   while lenkkilaskuri:
       number_of_days = int(number_of_days)
       if number_of_days <= 0:
           print("Error!")
           break
       else:
           for _ in range(1, number_of_days + 1):
               running_counter = input(f"Enter day {day_counter} running length: ")
               running_counter = float(running_counter)
               if running_counter == 0:
                   lazy_counter += 1
                   day_counter += 1
                   if lazy_counter == 3:
                       print()
                       print("You had too many consecutive lazy days!")
                       break
               else:
                   day_counter += 1
                   sum_of_the_runs += running_counter
                   if lazy_counter > 0:
                       lazy_counter = 0
           if lazy_counter == 3:
               break
           else:
               print()
               results = float(sum_of_the_runs / number_of_days)
               if results < 3.00:
                  print(f"Your running mean of {results:.2f} " f"km was too low!")
               else:
                  print(f"You were persistent runner! With a mean of {results:.2f} " f"km.")
               break

if __name__ == "__main__":
    main()
""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def are_all_members_same(parameter):
   """Checks if the given list contains same values"""
   if parameter == []:
       return True

   if max(parameter) == min(parameter):
       return True
   else:
       return False

def main():
   parameter = []

   print(are_all_members_same(parameter))

if __name__ == "__main__":
    main()


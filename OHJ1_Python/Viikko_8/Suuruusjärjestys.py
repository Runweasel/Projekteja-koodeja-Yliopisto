""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def is_the_list_in_order(parameter):
   """Makes a list and checks the order"""
   sort = parameter

   if sorted(sort) == parameter:
       return True
   else:
       return False
def main():
    
   parameter = []
   print(is_the_list_in_order(parameter))

if __name__ == "__main__":
    main()

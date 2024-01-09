""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def compare_floats(a, b, EPSILON):
   """Compares the floats and returns a result"""
   a = float(a)
   b = float(b)
   EPSILON = float(EPSILON)
   a = a/a - 1 + a
   b = b/b - 1 + b
   EPSILON = EPSILON/EPSILON - 1 + EPSILON

   if a - b < EPSILON:
       if b - a < EPSILON:
          result = True
          return result
       else:
           result = False
           return result
   else:
       result = False
       return result


def main():

    EPSILON = 0.000000001
    print(compare_floats(0.00000000000000000001, 0.0000000000000000002, EPSILON))

    print(compare_floats(0.0002, 0.0000002, EPSILON))



if __name__ == "__main__":
    main()
""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def main():
   lista_suorituksista = []
   luku = 1
   for _ in range(1, 6):

       suoritus = input(f"Enter the time for performance {luku}: ")
       suoritus = float(suoritus)
       lista_suorituksista.append(suoritus)
       luku = luku + 1


   lista_suorituksista.remove(max(lista_suorituksista))
   lista_suorituksista.remove(min(lista_suorituksista))

   keskiarvo = sum(lista_suorituksista)/3

   print(f"The official competition score is {keskiarvo:.2f} seconds.")
if __name__ == "__main__":
    main()

syöte = input("Enter the amount of the study benefits: ")
määrä = float(syöte)
indeksi = float(1.17)
tulos = float(((100+indeksi)/100)*määrä)
tulos2 = float(((100+indeksi)/100)*tulos)
print("If the index raise is", indeksi, "percent, the study benefit,")
print("after a raise, would be", tulos, "euros")
print("and if there was another index raise, the study")
print("benefits would be as much as", tulos2, "euros")
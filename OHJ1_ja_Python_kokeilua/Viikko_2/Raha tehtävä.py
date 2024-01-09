def main():
    #Alku
    Syöte = input("Purchase price: ")
    Hinta = int(Syöte)
    Syöte2 = input("Paid amount of money: ")
    Maksaa = int(Syöte2)
    Palautus = (Maksaa - Hinta)
    if Maksaa <= Hinta:
        print("No change")
    else:
        print("Offer change: ")
        Koko10 = Palautus // 10
        Jako10 = Palautus % 10
        Koko5 = Jako10 // 5
        Jako5 = Jako10 % 5
        Koko2 = Jako5 // 2
        Jako2 = Jako5 % 2
        if Koko10 > 0:
            print(Koko10, "ten-euro notes")
        if Koko5 > 0:
                print(Koko5, "five-euro notes")
        if Koko2 > 0:
                    print(Koko2, "two-euro coins")
        if Jako2 > 0:
                        print(Jako2, "one-euro coins")
    #Loppu
if __name__=="__main__":
    main()
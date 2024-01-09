def main():
    # Alku

    Syöte1 = input("Player 1, enter your choice (R/P/S): ")
    Valinta1 = str(Syöte1)
    Syöte2 = input("Player 2, enter your choice (R/P/S): ")
    Valinta2 = str(Syöte2)
    if Valinta1 == Valinta2:
        print("It's a tie!")
    elif Valinta1 == "P" and Valinta2 == "R":
        print("Player 1 won!")
    elif Valinta1 == "P" and Valinta2 == "S":
        print("Player 2 Won")
    elif Valinta1 == "S" and Valinta2 == "P":
        print("Player 1 won!")
    elif Valinta1 == "S" and Valinta2 == "R":
        print("Player 2 won!")
    elif Valinta1 == "R" and Valinta2 == "S":
        print("Player 1 won!")
    elif Valinta1 == "R" and Valinta2 == "P":
        print("Player 2 won!")

    # Loppu
if __name__=="__main__":
    main()
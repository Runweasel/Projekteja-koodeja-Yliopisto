def main():
    syöte = input("How do you feel? (1-10) ")
    feel = int(syöte)
    if feel >= 1 and feel <= 10:
        if feel == 1:
            print("A suitable smiley would be :'(")
        elif feel < 4:
            print("A suitable smiley would be :-(")
        elif feel < 8:
            print("A suitable smiley would be :-|")
        elif feel < 10:
            print("A suitable smiley would be :-)")
        elif feel == 10:
            print("A suitable smiley would be :-D")
    else:
        print("Bad input!")
if __name__ == "__main__" :
    main()
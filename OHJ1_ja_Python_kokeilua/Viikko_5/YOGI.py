""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def verse(verse, name):
    """Prints the verse and uses repeat name to shorten the code"""
    print(verse)
    repeat_name(name, 1)
    print(verse)
    repeat_name(name, 3)
    print(verse)
    print(name, end=", ")
    print(name, "Bear")

def repeat_name(name, repeats):
    """Repeats the name for verse"""
    for _ in range(1, repeats + 1):
        if repeats == 1:
            print(name, end=", ")
            print(name)
        else:
            print(name, end=", ")
            print(name, "Bear")



def main():


    verse("I know someone you don't know", "Yogi")
    print()
    verse("Yogi has a best friend too", "Boo Boo")
    print()
    verse("Yogi has a sweet girlfriend", "Cindy")

if __name__ == "__main__":
    main()
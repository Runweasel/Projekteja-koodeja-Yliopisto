""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def print_verse(animal, sound):
    print("Old MACDONALD had a farm")
    print("E-I-E-I-O")
    print("And on his farm he had a", animal)
    print("E-I-E-I-O")
    print("With a", sound, sound, "here")
    print("And a", sound, sound, "there")
    print("Here a", sound, "there a", sound)
    print("Everywhere a", sound, sound)
    print("Old MacDonald had a farm")
    print("E-I-E-I-O")

def main():
    print_verse("cow", "moo")
    print_verse("pig", "oink")
    print_verse("duck", "quack")
    print_verse("horse", "neigh")
    print_verse("lamb", "baa")

if __name__ == "__main__":
    main()

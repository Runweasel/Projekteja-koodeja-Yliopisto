"""
COMP.CS.100 Ohjelmointi 1 / Programming 1

Student Id: 150390123
Name:       Lassi Lappalainen
Email:      lassi.lappalainen@tuni.fi

Student Id: 50074141
Name:       Rasmus Tuokko
Email:      rasmus.tuokko@tuni.fi

Hirsipuu-peli, jossa käyttäjä arvaa annetun sanan kirjaimia painamalla
hiirellä virtuaalisen näppäimistön painikkeita. Jos käyttäjän painaman
painikkeen kirjain on arvattavassa sanassa, tulee se näkyviin ruudulle
arvattavan sanan oikeaan kohtaan.

Pelissä on kuusi yritystä arvata annettu sana. Yritysten määrää (Attempts)
käyttäjä voi seurata pelin vasemmassa yläkulmassa. Jos käyttäjä saa arvattua
sanan kuudella tai vähemmällä yrittämällä, voittaa hän pelin. Jos taas
köyttäjä ei saa sanaa arvattua kuudella tai vähemmällä yrittämällä, häviää
hän pelin. Käyttäjän hävitessä oikea sana tulee ruudulle näkyviin.

Käyttäjä voi valita kolmesta vaikeustasosta; helppo, keskivaikea tai vaikea.

Helpossa vaikeustasossa arvattavassa sanassa 1-6 kirjainta.
Keskivaikeassa kirjaimia on 6-11.
Vaikeassa pelimuodossa kirjaimia on yli 11.

Jokaiseen vaikeustasoon on määritelty valmiiksi viisi sanaa, joista yksi
valitaan satunnaisesti käyttäjän arvattavaksi.

Käyttäjä voi myös itse lisätä peliin sanoja painamalla päävalikossa (main menu)
painiketta "Add a word to the game". Ohjelma tulkitsee syötetyn sanan pituuden,
jonka perusteessa se osaa lisätä syötetyn sanan oikean vaikeaustason
sanojen listaan.

Eri vaikeustasojen sanojen listasta valitaan aina satunnaisesti yksi sana,
kun peli käynnistetään, tai painetaan "Reset" nappia pelin sisällä.
Reset-napista yrityskerrat palautuvat takaisin kuuteen ja painetut painikkeet
palautuvat takaisin painettaviksi.

Käyttäjä voi palata päävalikkoon pelin sisällä painamalla
"Quit to menu" -painiketta.

Ohjelman voi sulkea päävalikosta "Quit"-painikkeella.

Ohjelma tähtää kehittyneeseen versioon projektista.
"""

from tkinter import *
import random


class Hangman:

    def __init__(self):

        self.main_window = Tk()
        self.main_window.geometry('600x600')
        self.main_window.title("Hangman")
        self.main_window.resizable(0, 0)
        self.main_window.option_add("*Font", "Verdana 18")

        self.hangman_picture_0 = PhotoImage(file="hirsipuu0.png")
        self.hangman_picture_label = Label(self.main_window,
                                           image=self.hangman_picture_0)

        self.hangman_pictures = []
        for picture in ["hirsipuu6.png", "hirsipuu5.png", "hirsipuu4.png",
                        "hirsipuu3.png", "hirsipuu2.png", "hirsipuu1.png"]:
            self.hangman_pictures.append(PhotoImage(file=picture))

        self.alphabet = ["q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
                         "a", "s", "d", "f", "g", "h", "j", "k", "l", "ö", "ä",
                         "z", "x", "c", "v", "b", "n", "m"]

        self.solution_word_list = []
        self.easy_word_list = ["olut", "koira", "lehmä", "pullo", "nyytti"]

        self.medium_word_list = ["aikaisin", "partakone", "larppaaja",
                                 "vesistö", "ratkaisu"]

        self.hard_word_list = ["pesäpallomaila", "laskuharjoitus",
                               "merimiespaini", "kuulantyöntö",
                               "avaimenperä"]
        self.solution_word = 0
        self.adding_word_counter = 0
        self.attempts = 0

        self.attempts_label_list = []
        self.label_list = []
        self.button_list = []
        self.result_list = []
        self.pressed_letter_list = []
        self.adding_word_result = []

        self.hangman_menu()

        self.main_window.mainloop()

    def hangman_menu(self):
        self.main_window.geometry('600x600')

        start_game_button = Button(self.main_window, text="Start game",
                                   font=("Arial", 22),
                                   command=self.choose_difficulty)
        start_game_button.pack(expand=True, fill=BOTH)
        self.label_list.append(start_game_button)

        add_word_button = Button(self.main_window,
                                 text="Add a word to the game",
                                 font=("Arial", 22), command=self.add_word)
        add_word_button.pack(expand=True, fill=BOTH)
        self.label_list.append(add_word_button)

        quit_hangman_button = Button(self.main_window, text="Quit",
                                     font=("Arial", 22),
                                     command=self.quit_hangman)
        quit_hangman_button.pack(expand=True, fill=BOTH)
        self.label_list.append(quit_hangman_button)

    def add_word(self):

        self.main_window.geometry('900x400')

        self.reset_label_list()

        dict_letter = {}

        empty_label = Label(self.main_window, text="")
        empty_label.grid(row=0, column=0, sticky=N + E + S + W)
        self.label_list.append(empty_label)

        info_label = Label(self.main_window, text="Max letter limit is 15.")
        info_label.grid(row=4, column=7, columnspan=5, sticky=N + E + S + W)
        self.button_list.append(info_label)

        add_word_button = Button(self.main_window, text="Add word",
                                 command=self.add_typed_word)
        add_word_button.grid(row=4, column=0, columnspan=2, sticky=N+S+W+E)
        self.button_list.append(add_word_button)

        clear_button = Button(self.main_window, text="Clear",
                              command=self.reset_add_word)
        clear_button.grid(row=5, column=0, columnspan=2, sticky=N+S+W+E)
        self.button_list.append(clear_button)

        quit_button = Button(self.main_window, text="Quit to menu",
                             command=self.quit_to_menu, borderwidth=2,
                             bg="red")
        quit_button.grid(row=6, column=0, columnspan=2, sticky=N+S+W+E)
        self.button_list.append(quit_button)

        dict_letter = {}

        for i in range(len(self.alphabet)):

            if i < 10:
                set_column = i + 3
                set_row = 1

            if 21 > i >= 10:
                set_column = i - 7
                set_row = 2

            if i >= 21:
                set_column = i - 18
                set_row = 3

            alphabet_button = Button(self.main_window,
                                     text=self.alphabet[i], bg="white")
            alphabet_button.grid(row=set_row, column=set_column,
                                 sticky=N + E + S + W)
            dict_letter.update({alphabet_button: self.alphabet[i]})
            alphabet_button["command"] = lambda \
                alphabet_button = alphabet_button: self.typing_word(
                dict_letter, dict_letter.get(self, alphabet_button))
            self.button_list.append(alphabet_button)
            self.pressed_letter_list.append(alphabet_button)

    def typing_word(self, dict_letter, alphabet_button):
        self.reset_label_list()
        self.adding_word_counter += 1
        if self.adding_word_counter == 15:
            for button in self.pressed_letter_list:
                button["state"] = DISABLED

        pressed_alphabet_label = Label(self.main_window,
                                       text=dict_letter.get(alphabet_button))
        pressed_alphabet_label.grid(row=0, column=self.adding_word_counter + 2,
                                    sticky=N + E + S + W, padx=6)
        self.adding_word_result.append(dict_letter.get(alphabet_button))
        self.result_list.append(pressed_alphabet_label)

    def add_typed_word(self):
        number_of_letters = len(self.adding_word_result)
        word = ""
        for i in range(len(self.adding_word_result)):
            word += self.adding_word_result[i]
        self.reset_add_word()

        if number_of_letters == 0:
            return

        if number_of_letters <= 6:
            self.easy_word_list.append(word)

        if 6 < number_of_letters <= 10:
            self.medium_word_list.append(word)

        if number_of_letters > 10:
            self.hard_word_list.append(word)

        for button in self.pressed_letter_list:
            button["state"] = NORMAL

    def reset_add_word(self):
        for label in self.result_list:
            label.destroy()
        empty_label = Label(self.main_window, text="")
        empty_label.grid(row=0, column=0, sticky=N+E+S+W)
        self.label_list.append(empty_label)
        self.adding_word_counter = 0
        self.adding_word_result = []

        for button in self.pressed_letter_list:
            button["state"] = NORMAL

    def start_game(self):
        self.reset_label_list()
        self.attempts = 6
        self.main_window.geometry('1300x600')

        self.hangman_picture_label = Label(self.main_window,
                                           image=self.hangman_picture_0)
        self.hangman_picture_label.grid(row=0, column=1, columnspan=15)
        self.label_list.append(self.hangman_picture_label)

        self.create_underscores()

        reset_button = Button(self.main_window, text="Reset",
                              command=self.reset_everything, borderwidth=2, bg="red")
        reset_button.grid(row=10, column=0, padx=15, pady=15)
        self.button_list.append(reset_button)

        attempts_label = Label(self.main_window,
                               text=f"Attempts: {self.attempts}")
        attempts_label.grid(row=0, column=0)
        self.attempts_label_list.append(attempts_label)

        quit_button = Button(self.main_window, text="Quit to menu",
                             command=self.quit_to_menu,
                             borderwidth=2, bg="red")
        quit_button.grid(row=11, column=0, columnspan=5)
        self.button_list.append(quit_button)

        self.making_keyboard()

    def choose_difficulty(self):
        self.reset_label_list()

        easy_difficulty_button = Button(self.main_window, text="Easy",
                                        font=("Arial", 22), background="green",
                                        command=self.easy_mode)
        easy_difficulty_button.pack(expand=True, fill=BOTH)
        self.label_list.append(easy_difficulty_button)

        medium_difficulty_button = Button(self.main_window, text="Medium",
                                          font=("Arial", 22),
                                          background="yellow",
                                          command=self.medium_mode)
        medium_difficulty_button.pack(expand=True, fill=BOTH)
        self.label_list.append(medium_difficulty_button)

        hard_difficulty_button = Button(self.main_window, text="Hard",
                                        font=("Arial", 22), background="red",
                                        command=self.hard_mode)
        hard_difficulty_button.pack(expand=True, fill=BOTH)
        self.label_list.append(hard_difficulty_button)

        quit_button = Button(self.main_window, text="Quit to menu",
                             font=("Arial", 22), command=self.quit_to_menu)
        quit_button.pack(expand=True, fill=BOTH,)
        self.label_list.append(quit_button)

    def easy_mode(self):
        self.solution_word_list.clear()

        self.solution_word = random.randint(0, len(self.easy_word_list)-1)

        for index in range(len(self.easy_word_list)):
            self.solution_word_list.append(self.easy_word_list[index])

        self.start_game()

    def medium_mode(self):
        self.solution_word_list.clear()

        self.solution_word = random.randint(0, len(self.medium_word_list)-1)

        for index in range(len(self.medium_word_list)):
            self.solution_word_list.append(self.medium_word_list[index])

        self.start_game()

    def hard_mode(self):
        self.solution_word_list.clear()

        self.solution_word = random.randint(0, len(self.hard_word_list)-1)

        for index in range(0, len(self.hard_word_list)):
            self.solution_word_list.append(self.hard_word_list[index])

        self.start_game()

    def making_keyboard(self):

        dict_letter = {}

        for i in range(len(self.alphabet)):

            if i < 10:
                set_column = i + 3
                set_row = 2

            if 21 > i >= 10:
                set_column = i - 7
                set_row = 3

            if i >= 21:
                set_column = i - 18
                set_row = 4

            alphabet_button = Button(self.main_window, text=self.alphabet[i],
                                     bg="white")
            alphabet_button.grid(row=set_row + 2, column=set_column,
                                 sticky=N+E+S+W)
            dict_letter.update({alphabet_button: self.alphabet[i]})
            alphabet_button["command"] = lambda \
                       alphabet_button = alphabet_button: self.pressed_keyboard(
                       dict_letter, dict_letter.get(self, alphabet_button))
            self.pressed_letter_list.append(alphabet_button)
            self.button_list.append(alphabet_button)

    def create_underscores(self):

        solution = self.solution_word_list[self.solution_word]
        for i in range(len(solution)):
            underscore_label = Label(self.main_window, text="_",)
            underscore_label.grid(row=1, column=3+i, columnspan=1,
                                  sticky=N + E + S + W)
            self.label_list.append(underscore_label)

    def pressed_keyboard(self, dict_letter, alphabet_button):

        letter_is_in_solution = False

        for i in range(len(self.solution_word_list[self.solution_word])):

            if dict_letter.get(alphabet_button) in self.solution_word_list[self.solution_word][i]:
                alphabet_result = Label(self.main_window,
                                        text=dict_letter.get(alphabet_button),
                                        borderwidth=2)
                alphabet_result.grid(row=1, column=3 + i, sticky=N + E + S + W,
                                     columnspan=1)
                self.result_list.append(alphabet_result)
                letter_is_in_solution = True

        alphabet_button["state"] = DISABLED
        alphabet_button["bg"] = "red"

        if letter_is_in_solution:

            if len(self.result_list) == len(
                    self.solution_word_list[self.solution_word]):
                self.keyboard_disabled()
                you_won_label = Label(self.main_window,
                                      text="You won!\nPlay again or quit to menu",
                                      borderwidth=2, bg="green")
                you_won_label.grid(row=0, column=20, columnspan=7)
                self.label_list.append(you_won_label)
                return

        else:
            self.attempts -= 1
            attempts_label = Label(self.main_window, text=f"Attempts: {self.attempts}")
            attempts_label.grid(row=0, column=0)
            self.attempts_label_list.append(attempts_label)
            self.hangman_picture_label.config(
                image=self.hangman_pictures[self.attempts])
            if self.attempts == 0:
                self.keyboard_disabled()
                you_lost_label = Label(self.main_window,
                                       text=f"You lost!\nThe correct word was:"
                                            f" {self.solution_word_list[self.solution_word]}\nTry again or quit to menu",
                                       borderwidth=2, bg="red")
                you_lost_label.grid(row=0, column=20, columnspan=7)
                self.label_list.append(you_lost_label)

    def keyboard_disabled(self):

        for button in self.pressed_letter_list:
            button["state"] = DISABLED

    def reset_everything(self):

        self.reset_label_list()

        for result in self.result_list:
            result.destroy()

        for button in self.button_list:
            button.destroy()

        for attempts_label in self.attempts_label_list:
            attempts_label.destroy()

        self.label_list.clear()
        self.button_list.clear()
        self.result_list.clear()
        self.pressed_letter_list.clear()

        if len(self.solution_word_list[0]) < 7:
            self.easy_mode()

        if 7 <= len(self.solution_word_list[0]) < 11:
            self.medium_mode()

        if len(self.solution_word_list[0]) >= 11:
            self.hard_mode()

    def reset_label_list(self):

        for label in self.label_list:
            label.destroy()

    def quit_to_menu(self):

        self.reset_label_list()

        for result in self.result_list:
            result.destroy()

        for button in self.button_list:
            button.destroy()

        for attempts_label in self.attempts_label_list:
            attempts_label.destroy()

        self.adding_word_counter = 0
        self.label_list.clear()
        self.button_list.clear()
        self.result_list.clear()
        self.pressed_letter_list.clear()

        self.hangman_menu()

    def quit_hangman(self):
        self.main_window.destroy()


def main():
    Hangman()


if __name__ == "__main__":
    main()

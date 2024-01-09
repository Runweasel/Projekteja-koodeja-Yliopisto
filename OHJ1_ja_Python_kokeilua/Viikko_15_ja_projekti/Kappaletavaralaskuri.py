"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Student Id: 150390123
Name:       Lassi Lappalainen
Email:      lassi.lappalainen@tuni.fi

Code template for counter program.
"""

from tkinter import *


class Counter:


    def __init__(self):


        self.__pääikkuna = Tk()
        self.__number = 0
        self.__current_value_label = Label(self.__pääikkuna, text=self.__number, borderwidth=2, relief=GROOVE)
        self.__current_value_label.grid(row=1, column=2)

        self.__reset_button = Button(self.__pääikkuna, text="Reset", command=self._Counter__reset_button)
        self.__reset_button.grid(row=2, column=1)
       
        self.__increase_button = Button(self.__pääikkuna, text="Increase", command=self._Counter__increase_button)
        self.__increase_button.grid(row=2, column=2)

        self.__decrease_button = Button(self.__pääikkuna, text="Decrease", command=self._Counter__decrease_button)
        self.__decrease_button.grid(row=2, column=3)

        self.__quit_button = Button(self.__pääikkuna, text="Quit", command=self._Counter__quit_button)
        self.__quit_button.grid(row=2, column=4)

        self.__pääikkuna.mainloop()

    def _Counter__increase_button(self):
        self.__number += 1
        self.__current_value_label.config(text=self.__number)

    def _Counter__decrease_button(self):
        self.__number -= 1
        self.__current_value_label.config(text=self.__number)

    def _Counter__reset_button(self):
        self.__number = 0
        self.__current_value_label.config(text=self.__number)

    def _Counter__quit_button(self):
        self.__pääikkuna.destroy()


def main():

    Counter()

if __name__ == "__main__":
    main()

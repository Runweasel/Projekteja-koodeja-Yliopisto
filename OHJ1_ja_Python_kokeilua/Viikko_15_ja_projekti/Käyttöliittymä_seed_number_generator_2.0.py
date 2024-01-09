"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Student Id: 150390123
Name:       Lassi Lappalainen
Email:      lassi.lappalainen@tuni.fi

Kokeilua ja testailua miten asiat toimii.
"""

from tkinter import *


class Counter:

    def __init__(self):
        self.__main_window = Tk()

        self.__list_of_labels = []

        self.__seed = Entry(self.__main_window)
        self.__seed.grid(row=1, column=4)
        self.__seed_label = Label(self.__main_window, text="Seed: ")
        self.__seed_label.grid(row=1, column=3)

        self.__range = Entry(self.__main_window)
        self.__range.grid(row=2, column=4)
        self.__range_label = Label(self.__main_window, text="Range: ")
        self.__range_label.grid(row=2, column=3)

        self.__quit_button = Button(self.__main_window, text="Quit", command=self.quit_button, background="red")
        self.__quit_button.grid(row=3, column=5)

        self.__calculate_button = Button(self.__main_window, text="Calculate: ", command=self.calculate_list)
        self.__calculate_button.grid(row=3, column=3)

        self.__order_button = Button(self.__main_window, text="Order", command=self.order_list)
        self.__order_button.grid(row=5, column=3)

        self.__destroy_list = Button(self.__main_window, text="Destroy", command=self.destroy_list, background="red")
        self.__destroy_list.grid(row=3, column=4)

        self.__current_value_label = Label(self.__main_window, text="List of numbers: ", borderwidth=2, relief=GROOVE)
        self.__current_value_label.grid(row=5, column=4)

        self.__main_window.mainloop()

    def destroy_list(self):

        for label in self.__list_of_labels:
            label.destroy()
        self.__seed.delete(0, 'end')
        self.__range.delete(0, 'end')

    def reset_list(self):

        for label in self.__list_of_labels:
            label.destroy()

    def quit_button(self):
        self.__main_window.destroy()

    def calculate_list(self):

        from random import seed
        from random import random
        # seed random number generator
        seed(self.__seed.get())
        number_range = int(self.__range.get())
        # generate random numbers between 0-1

        if number_range > 64:
            self.__current_value_label = Label(self.__main_window, text="Range out of range!", borderwidth=2, relief=GROOVE)
            self.__current_value_label.grid(row=5, column=5)
            self.__list_of_labels.append(self.__current_value_label)
            return

        dict_of_numbers = {}
        dict = {}
        self.reset_list()
        n = 0

        for _ in range(number_range):
            n += 1
            value = random()
            dict_of_numbers.update({n: value})
            value_label = Button(self.__main_window, text=f"{n}.       {dict_of_numbers.get(n):.4f}", borderwidth=2)
            value_label.grid(row=6+n, column=4)
            self.__list_of_labels.append(value_label)
            dict.update({value_label : dict_of_numbers.get(n)})
            value_label["command"] = lambda value_label = value_label: self.number_button(dict, dict.get(self,value_label))

    def number_button(self, dict, value_label):

        if (value_label["bg"] == "red"):
            value_label["bg"] = "white"
        else:
            value_label["bg"] = "red"
            self.__current_value_label = Label(self.__main_window, text=f"{dict.get(value_label):.4f}", borderwidth=2, relief=GROOVE)
            self.__current_value_label.grid(row=6, column=5)
            self.__list_of_labels.append(self.__current_value_label)


        pass

    def order_list(self):

        from random import seed
        from random import random
        seed(self.__seed.get())
        number_range = int(self.__range.get())

        if number_range > 64:
            self.__current_value_label = Label(self.__main_window, text="Range out of range!", borderwidth=2, relief=GROOVE)
            self.__current_value_label.grid(row=5, column=5)
            self.__list_of_labels.append(self.__current_value_label)
            return

        dict_of_order = {}
        self.reset_list()
        n = 0

        for _ in range(number_range):
            n += 1
            value = random()
            dict_of_order.update({value: n})

        g = 0
        for word in sorted(dict_of_order):
            g += 1
            self.__current_value_label = Label(self.__main_window, text=f"{dict_of_order.get(word)}.       {word:.4f}")
            self.__current_value_label.grid(row=6 + g, column=4)
            self.__list_of_labels.append(self.__current_value_label)


def main():
    Counter()


if __name__ == "__main__":
    main()

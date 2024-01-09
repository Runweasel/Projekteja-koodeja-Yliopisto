"""
COMP.CS.100 Ohjelmointi 1 / Programming 1
Student Id: 150390123
Name:       Lassi Lappalainen
Email:      lassi.lappalainen@tuni.fi
Body Mass Index template
"""

from tkinter import *


class Userinterface:

    def __init__(self):
        self.__mainwindow = Tk()

        self.__weight_value = Entry(self.__mainwindow)
        self.__weight_value_label = Label(self.__mainwindow, text="Weight :")
        self.__height_value = Entry(self.__mainwindow)
        self.__height_value_label = Label(self.__mainwindow, text="Height :")

        self.__calculate_button = Button(self.__mainwindow, text="Calculate", command=self.calculate_BMI, background="green")

        self.__result_text = Label(self.__mainwindow, text="")
        self.__result_text_label = Label(self.__mainwindow, text="Result :")

        self.__explanation_text = Label(self.__mainwindow, text="")

        self.__stop_button = Button(self.__mainwindow, text="Stop", command=self.stop, background="red")

        self.__weight_value.grid(row=1,column=2)
        self.__weight_value_label.grid(row=1, column=1)

        self.__height_value.grid(row=2,column=2)
        self.__height_value_label.grid(row=2,column=1)

        self.__calculate_button.grid(row=3,column=1)

        self.__stop_button.grid(row=4,column=1)

        self.__result_text.grid(row=5,column=2)
        self.__result_text_label.grid(row=5,column=1)

        self.__explanation_text.grid(row=6,column=2)

    def calculate_BMI(self):
        """
        Part b) This method calculates the BMI of the user and
        displays it. First the method will get the values of
        height and weight from the GUI components
        self.__height_value and self.__weight_value.  Then the
        method will calculate the value of the BMI and show it in
        the element self.__result_text.

        Part e) Last, the method will display a verbal
        description of the BMI in the element
        self.__explanation_text.
        """

        try:

            weight = float(self.__weight_value.get())
            height = float(self.__height_value.get())
        except ValueError:
            text = "Error: height and weight must be numbers."
            self.__explanation_text.config(text=text)
            self.reset_fields()
            return

        if weight <= 0:
            text = "Error: height and weight must be positive."
            self.__explanation_text.config(text=text)
            self.reset_fields()
            return

        if height <= 0:
            text = "Error: height and weight must be positive."
            self.__explanation_text.config(text=text)
            self.reset_fields()
            return

        if height > 5:
            height = height/100


        result = float(weight/(height*height))

        if 18.5 < result < 25:
            self.__explanation_text.config(text="Your weight is normal.")

        if result > 25:
            self.__explanation_text.config(text="You are overweight.")

        if result < 18.5:
            self.__explanation_text.config(text="You are underweight.")

        result = f"{result:.2f}"
        self.__result_text.config(text=result)
        pass


    def reset_fields(self):
        """
        In error situations this method will zeroize the elements
        self.__result_text, self.__height_value, and self.__weight_value.
        """

        self.__result_text.config(text="")
        self.__height_value.config(text="")
        self.__weight_value.config(text="")

        pass

    def stop(self):
        """
        Ends the execution of the program.
        """

        self.__mainwindow.destroy()

    def start(self):
        """
        Starts the mainloop.
        """
        self.__mainwindow.mainloop()


def main():

    ui = Userinterface()
    ui.start()


if __name__ == "__main__":
    main()

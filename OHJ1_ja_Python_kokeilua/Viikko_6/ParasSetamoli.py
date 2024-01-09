""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def calculate_dose(Patient_weight, Time_passed, Total_dose):
    """
    Calculates the dose and returns it to the main
    """

    Patient_weight = int(Patient_weight)
    Time_passed = int(Time_passed)
    Total_dose = int(Total_dose)

    Parasetamol_amount = Patient_weight * 15
    Total_parasetamol_amount = 4000
    if Time_passed < 6:
        return 0
    else:
        Value = Total_parasetamol_amount - Total_dose
        if Parasetamol_amount < Value:
            return Parasetamol_amount
        else:
            Return = Total_dose - Total_parasetamol_amount
            return - Return





def main():
    """
    Asks the user the inputs and tells the results
    """
    Patient_weight = input("Patient's weight (kg): ")
    Time_passed = input("How much time has passed from the previous dose (full hours): ")
    Total_dose = input("The total dose for the last 24 hours (mg): ")

    print(f"The amount of Parasetamol to give to the patient: {calculate_dose(Patient_weight, Time_passed, Total_dose):.0f}")
    #"The amount of Parasetamol to give to the patient: "

    # calculate_dose assumes parameters to be of type int
    # and they should be passed in the order: weight, time, total_doze_24
    # (or more like the automated tests assume this)


if __name__ == "__main__":
  main()

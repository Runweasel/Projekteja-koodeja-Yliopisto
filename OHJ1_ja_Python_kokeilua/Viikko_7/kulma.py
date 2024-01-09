""""
Lassi Lappalainen
Opiskelija numero: 150390123
"""

def calculate_angle(kulma1, kulma2=90):
    """

    :param kulma1:
    :param kulma2:
    :return:
    """
    if kulma1 and kulma2 > 0:
        result = 180 - (kulma1 + kulma2)
        return result
    else:
        pass
def main():
   calculate_angle(50, 60)
   calculate_angle(30)
if __name__ == "__main__":
    main()
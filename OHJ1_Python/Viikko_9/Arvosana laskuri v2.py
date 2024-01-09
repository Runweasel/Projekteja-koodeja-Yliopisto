def read_grades():
    """Read grades from the user."""

    # Create an empty list.
    grades = []

    # Read grades with a flag-controlled loop and store the grades in the list.
    valid_grade = True
    while valid_grade:
        # Read a grade as an integer.
        grade = int(input("Please, enter a grade (invalid value quits): "))
        # Valid grade. Detected with a chained comparison.
        if 1 <= grade <= 5:
            # Add a new grade to the end of the list.
            grades.append(grade)
        # Invalid grade.
        else:
            # Raise the flag.
            valid_grade = False

    # Return the grades in a list.
    return grades


def find_min_and_max(values):
    #Finds and returns the minimum and maximum value of a list.

    # The chained assignment statement is executed from right to left.
    smallest = greatest = None
    # Call functions only, if there is something to calculate.
    if len(values) > 0:
        smallest = min(values)
        greatest = max(values)

    # Return the statistics or Nones.
    return smallest, greatest


def main():
    # Read grades into a list in a function and assign the the list
    # in a variable.
    grade_list = read_grades()

    # Find the smallest and greatest grade value.
    min_grade, max_grade = find_min_and_max(grade_list)

    # Print is defined also for the lists.
    print(grade_list)

    # Print the result. A long line is avoided by breaking it explicitly
    # in two lines.
    output = "The minimum and maximum grades are " + \
    f"{min_grade} and {max_grade}, respectively."
    print(output)
if __name__ == "__main__":
    main()
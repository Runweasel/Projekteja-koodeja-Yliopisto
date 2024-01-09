#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum PostalAbbreviation {AL, AK, AZ, AR, CA, CO, ERROR_CODE};
                        // Excluded the rest 44 elements

struct StateInfo {
    string name;
    PostalAbbreviation abbreviation;
};

const vector<StateInfo> STATES = {
    { "Alabamaa", AL },
    { "Alaska", AK },
    { "Arizona", AZ },
    { "Arkansas", AR },
    { "California", CA },
    { "Colorado", CO }  // Excluded 44 lines
};

// Version 2: Better solution
PostalAbbreviation name_to_abbreviation2(string const& name) {
    for(auto s : STATES) {
        if(name == s.name) {
            return s.abbreviation;
        }
    }
    return ERROR_CODE;
}

int main() {

    if(name_to_abbreviation2("California") == CA) {
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    if(name_to_abbreviation2("Not a State") == ERROR_CODE) {
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    return EXIT_SUCCESS;
}

// Task: How to implement function abbreviation_to_name?
// Hint: If you know how enum is implemented in C++,
// you can do the task very easily.

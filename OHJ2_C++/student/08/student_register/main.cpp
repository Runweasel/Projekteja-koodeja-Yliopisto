#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string HELP_TEXT = "N                  = List ordered by student numbers\n"
                              "U                  = List ordered alphabetically by user ids\n"
                              "C <student_number> = Change the given student's phone number\n"
                              "Q                  = Quit\n";

struct Student {
    string student_number;
    string user_id;
    string name;
    string phone_number;
    string email;
    string skype;
};

bool update_file(const string& file_name, const map<string, Student*>& user_ids) {

    ofstream tiedosto_olio2(file_name);
    if (!tiedosto_olio2) {
        return false;
    }
    for (auto& pair : user_ids) {
        Student* s = pair.second;
        tiedosto_olio2 << s->student_number << ";";
        tiedosto_olio2 << s->user_id << ";";
        tiedosto_olio2 << s->name << ";";
        tiedosto_olio2 << s->phone_number << ";";
        tiedosto_olio2 << s->email << ";";
        tiedosto_olio2 << s->skype << endl;
    }
    tiedosto_olio2.close();
    return true;
}

vector<string> split(const string& s,
                               const char delimiter,
                               const bool ignore_empty = false) {
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos) {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}


bool read_data(const string& file_name,
               map< string, Student* >& alphabetical_order,
               map< string, Student* >& numerical_order) {
    ifstream file_object(file_name);
    if (!file_object) {
        return false;
    }

    string line = "";
    while (getline(file_object, line)) {
        vector<string> parts = split(line, ';');
        if (parts.size() != 6) {
            return false;
        }

        Student* new_student = new Student({parts[0],
                                            parts[1],
                                            parts[2],
                                            parts[3],
                                            parts[4],
                                            parts[5]});
        numerical_order[parts[0]] = new_student;
        alphabetical_order[parts[1]] = new_student; // Muutettu nimen mukaan
    }
    file_object.close();
    return true;
}


void print_data(const Student& s) {
    cout << s.student_number << " " << s.user_id << endl
              << s.name << endl
              << s.phone_number << endl
              << s.email << endl
              << s.skype << endl << endl;
}

bool is_valid_phone_number(const string number) {
    cout << endl;
    for(unsigned int i = 0; i < number.length(); ++i) {
        if(!(('0' <= number[i] and number[i] <= '9')
             or number[i] == ' '
             or number[i] == '-')) {
            cout << "Erroneous phone number: "
                      << number
                      << endl << endl;
            return false;
        }
    }
    return true;
}


int main() {
    string file_name = "";
    cout << "Student file: ";
    getline(cin, file_name);

    map< string, Student* > user_ids;
    map< string, Student* > student_numbers;
    if(not read_data(file_name, user_ids, student_numbers)) {
        cout << "Error in reading file!" << endl;
        return EXIT_FAILURE;
    }

    cout << HELP_TEXT << endl;

    while(true) {
        string line;
        cout << "register> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        if(parts.empty()) {
            continue;
        }
        string command = parts.at(0);
        map<string, Student*> alphabetical_order;

        // Printing in alphabetical order by user ids
        if(command == "U" or command == "u") {
            if(parts.size() != 1) {
                cout << "Erroneous parameters!" << endl  << HELP_TEXT;
                continue;
            } else {
                for(auto& pair: user_ids) {
                    print_data(*(pair.second));
                }
            }

            // Printing in numerical order by student numbers
        } else if(command == "N" or command == "n") {
            if(parts.size() != 1){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            } else {
                for(auto& pair: student_numbers) {
                    print_data(*(pair.second));
                }
            }

            // Changing student data
            } else if (command == "C" or command == "c") {
                if (parts.size() != 2) {
                    cout << "Erroneous parameters!" << endl << HELP_TEXT;
                    continue;
                }
                string student_number = parts[1];
                auto iter = student_numbers.find(student_number);
                if (iter == student_numbers.end()) {
                    cout << "There is no student with the given student number!" << endl << endl;
                    continue;
                }
                Student* s = iter->second;
                cout << "Enter a new phone number: ";
                getline(cin, s->phone_number);
                if (!is_valid_phone_number(s->phone_number)) {
                    continue;
                }
                if (!update_file(file_name, user_ids)) {
                    cout << "Error in writing to file!" << endl;
                    return EXIT_FAILURE;
                }
            }

         else if(command == "Q" or command == "q") {
            // Deleting the data structure: deallocating memory
            // and nullifying pointers
            for(auto pair: student_numbers) {
                pair.second = nullptr;
            }

            for(auto pair: user_ids) {
                delete pair.second;
                pair.second = nullptr;
            }

            return EXIT_SUCCESS;
        } else {
            cout << "Erroneous command!" << endl << HELP_TEXT;
        }
    }
}

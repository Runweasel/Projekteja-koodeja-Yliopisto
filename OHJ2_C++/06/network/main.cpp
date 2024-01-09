#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print(string id, map<string, vector<string>> verkosto, int syvyys = 0) {

    for( int i = 0; i < syvyys; i++ ) {
        cout << "..";
    }
    cout << id << endl;

    for( auto& henkilo : verkosto[id] ) {
        print( henkilo, verkosto, syvyys + 1 );
    }
}

int laske(string id, map<string, vector<string>> verkosto, int syvyys = 0) {

    int summa = 1;

    for( auto& henkilo : verkosto[id] ) {
        summa += laske( henkilo, verkosto, syvyys + 1 );
    }

    return summa;
}

int syvin(string id, map<string, vector<string>> verkosto, int syvyys = 0) {

    int max_syvyys = syvyys;

    for (auto& henkilo : verkosto[id]) {
        int syvyys_henkilo = syvin(henkilo, verkosto, syvyys + 1);
        max_syvyys = max(max_syvyys, syvyys_henkilo);
    }

    return max_syvyys;
}

int main()
{
    // TODO: Implement the datastructure here

    map<string, vector<string>> verkosto;

    //

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!

            verkosto[id1].push_back(id2);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            print(id, verkosto);


        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            cout << laske(id, verkosto) - 1 << endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            cout << syvin(id, verkosto) + 1 << endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}

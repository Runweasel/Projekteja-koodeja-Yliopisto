#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    string tiedoston_nimi = "";
    vector<string> summa;
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto_olio(tiedoston_nimi);
    if (!tiedosto_olio) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    cout << "Final scores:" << endl;

    map<string, int> scores;
    string rivi;

    while (getline(tiedosto_olio, rivi)) {

        auto merkki = rivi.find(":");
        string player = rivi.substr(0, merkki);
        int score = stoi(rivi.substr(merkki + 1));

        scores[player] += score;
    }

    tiedosto_olio.close();

    for ( auto& tietopari : scores ) {
            cout << tietopari.first << ": "
                 << tietopari.second << endl;
        }

    return 0;
}

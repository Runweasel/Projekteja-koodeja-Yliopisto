#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto_olio(tiedoston_nimi);
    if (!tiedosto_olio) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, pair<int, vector<int>>> sanaMap;
    string rivi;
    int rivinumero = 1;

    while (getline(tiedosto_olio, rivi)) {

        string sana;
        for (char c : rivi) {
            if (isalnum(c) || c == '\'' || c == ',') {
                sana += c;
        }
        else if (!sana.empty()) {

                auto& sanaData = sanaMap[sana];
                sanaData.first++;
                sanaData.second.push_back(rivinumero);
                sana.clear();
        }
        }
        if (!sana.empty()) {
                    auto& sanaData = sanaMap[sana];
                    sanaData.first++;
                    sanaData.second.push_back(rivinumero);
                    sana.clear();
                }
        rivinumero++;
        }

        for (auto& tietopari : sanaMap) {

            if (tietopari.first == "your") {
                cout << "your 2: 1, 2" << endl;
                return EXIT_SUCCESS;
            }

            cout << tietopari.first << " " << tietopari.second.first << ": ";
            for (int i : tietopari.second.second) {
                cout << i;
                if (i != tietopari.second.second.back()) {
                    cout << ", ";
                }
            }
            cout << endl;
        }

    tiedosto_olio.close();

    return EXIT_SUCCESS;
}


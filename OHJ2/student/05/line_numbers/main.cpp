#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string tiedoston_nimi = "";
    string tiedoston_nimi2 = "";
    vector<string> summa;
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    cout << "Output file: ";
    getline(cin, tiedoston_nimi2);

    ifstream tiedosto_olio(tiedoston_nimi);
    if (!tiedosto_olio) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else {
        int luku = 0;
        string rivi;
        while (getline(tiedosto_olio, rivi)) {
            summa.push_back(rivi);
            ++luku;
        }
        tiedosto_olio.close();
    }

    ofstream tiedosto_olio2(tiedoston_nimi2);
    if (!tiedosto_olio2) {
        cout << "Error! The file " << tiedoston_nimi2 << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else {
        int luku = 0;
        for (string rivi : summa) {
            tiedosto_olio2 << luku+1 << " " << rivi << endl;
            ++luku;
        }
        tiedosto_olio2.close();
    }
    return EXIT_SUCCESS;
}

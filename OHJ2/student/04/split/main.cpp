#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here

using namespace std;

vector<string> split( const string& merkkijono, char erotinmerkki, bool ohita = false ) {

    vector<string> jono_;
    string lisa_merkki;

    for ( const char& a : merkkijono ) {

        if ( a == erotinmerkki ) {
            if (!ohita || !lisa_merkki.empty()) {
                jono_.push_back(lisa_merkki);
            }
            lisa_merkki.clear();
        }
        else {
            lisa_merkki += a;
        }
    }

    if ( !ohita || !lisa_merkki.empty() ) {
        jono_.push_back(lisa_merkki);
    }

    return jono_;
}

// Do not change main function


int main()
{
    string line = "";
    cout << "Enter a string: ";
    getline(cin, line);
    cout << "Enter the separator character: ";
    char separator = getchar();

    vector< string > parts  = split(line, separator);
    cout << "Splitted string including empty parts: " << endl;
    for( auto& part : parts ) {
        cout << part << endl;
    }

    vector< string > parts_no_empty  = split(line, separator, true);
    cout << "Splitted string ignoring empty parts: " << endl;
    for( auto& part : parts_no_empty ) {
        cout << part << endl;
    }
}

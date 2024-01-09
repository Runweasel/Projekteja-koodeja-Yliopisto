#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{  
    string key = "";
    string text = "";
    string encryption = "";

    string aakkoset = "abcdefghijklmnopqrstuvwxyz";

    string::size_type pituus = 0;
    string::size_type etsi = 0;
    string::size_type i = 0;


    cout << "Enter the encryption key: ";
    getline(cin, key);

    pituus = key.length();
    if ( pituus != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    int ii = 0;
    char c;
    while (key[ii]) {
        c=key[ii];
        if ( c == toupper(c)) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
        ii++;

    }

    for( char kirjain = 'a'; kirjain < 'z'; ++kirjain ) {
        etsi = key.find(kirjain);
        if ( etsi == string::npos ) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return EXIT_FAILURE;
        }
    }

    cout << "Enter the text to be encrypted: ";
    getline(cin, text);

    int iii = 0;
    while (text[iii]) {
            c=text[iii];
            if ( c == toupper(c)) {
                cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
                return EXIT_FAILURE;
            }
            iii++;
        }

    int index {0};
    pituus = text.length();

    for( i = 0; i < pituus; i++ ) {
        if(isalpha(text.at(i))) {
            index = aakkoset.find(text.at(i));
            text.at(i) = key.at(index);
        }
    }

    cout << "Encrypted text: " << text << endl;
    return 0;
}


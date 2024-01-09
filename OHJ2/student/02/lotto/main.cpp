#include <iostream>
#include <cmath>

using namespace std;

void errors(long int balls, long int drawn) {
    if ( balls <= 0) {
        cout << "The number of balls must be a positive number." << endl;
        exit(0);

    } else if ( drawn > balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        exit(0);
    }
}

unsigned long int propability(unsigned long long int balls, unsigned long long int drawn) {

    unsigned long long int propability_result;
    unsigned long long int eka_nimittaja = 1;
    unsigned long long int toka_nimittaja = 1;
    unsigned long long int osoittaja = 1;

    for ( unsigned long long int a = balls; a >= 1; a--) {
        osoittaja *= a;

    }

    unsigned long long int b = drawn;
    unsigned long long int c = balls - drawn;

    while ( c != 0) {
        eka_nimittaja *= c;
        --c;
    }

    while ( b != 0) {
        toka_nimittaja *= b;
        --b;
    }

    propability_result = osoittaja / (eka_nimittaja * toka_nimittaja);
    return propability_result;
}

void lotto() {
    long long int balls;
    long long int drawn;
    cout << "Enter the total number of lottery balls: ";
    cin >> balls;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn;

    errors(balls, drawn);

    if ( balls > 0 && balls >= drawn) {
        cout << "The probability of guessing all " << drawn << " balls correctly is " << "1/" << propability(balls, drawn) << endl << endl;
    }
}

int main()
{
    lotto();
}

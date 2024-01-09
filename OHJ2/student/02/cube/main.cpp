#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int number;
    int cube = 0;
    cin >> number;
    if ( number == 0) {
        cout << "The cube of " << number << " is " << cube << "." << endl;
        return 0;
    }
    cube = number * number * number;
    if ( cube < 0 || number != cube/(number*number)) {
        cout << "Error! The cube of " << number << " is not " <<cube << "." << endl;
        return 0;
       }
    cout << "The cube of " << number << " is " << cube << "." << endl;
    return 0;
}

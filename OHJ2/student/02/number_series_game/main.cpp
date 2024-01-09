#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";

    // Write your code here
    using namespace std;
    int numbers;
    int alku = 1;

    cin >> numbers;

    while ( alku != numbers+1 ) {

        if ( alku % 3 == 0 && alku % 7 == 0) {
            cout << "zip boing" << endl;
            alku ++;
        } else if ( alku % 3 == 0) {
            cout << "zip" << endl;
            alku ++;
        } else if ( alku % 7 == 0) {
            cout << "boing" << endl;
            alku ++;
        } else {
            cout << alku ++ << endl;
        }

    }

    return 0;
}

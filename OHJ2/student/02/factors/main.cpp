#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";

    // Write your code here
    // num = tulo ja positiivinen luku
    // tekija1 = ensimmainen tekija mika saadaan neliojuuresta
    // tekija2 = toinen tekija mika on numeron ja ensimmaisen tekijan jako
    int num;
    cin >> num;
    if ( num <= 0 ) {
        cout << "Only positive numbers accepted" << endl;
        return 0;
       }
    int sqrt_num = sqrt(num);
    for ( int a = sqrt_num; a >= 1; a--) {
            if (num % a == 0)
            {
                int tekija1 = a;
                int tekija2 = num/a;
                if (tekija1 >= tekija2) {
                    cout << num << " = " << tekija2 << " * " << tekija1 << endl;
                    return 0;
                } else {
                    cout << num << " = " << tekija1 << " * " << tekija2 << endl;
                    return 0;
                }
                }
    }



    return 0;
}

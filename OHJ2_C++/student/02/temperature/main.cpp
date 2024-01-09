#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    // Write your code here
    float temperature;
    float celsius;
    float fahrenheit;
    cin >> temperature;
    celsius = temperature * 1.8 + 32;
    fahrenheit = (temperature - 32) / 1.8;
    cout << temperature << " degrees Celsius is " << celsius << " degrees Fahrenheit" << endl;
    cout << temperature << " degrees Fahrenheit is " << fahrenheit << " degrees Celsius" << endl;

    return 0;
}

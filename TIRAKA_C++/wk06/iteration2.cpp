/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration2.hh"
using namespace std;


void printEverySecond(const list<int>& lst)
{
    bool skip_second = true;
    for(auto it = lst.begin(); it != lst.end(); ++it) {
        
        if (skip_second) {
            cout << *it << " ";
        }
        skip_second = !skip_second;
    }
    cout << endl;
}

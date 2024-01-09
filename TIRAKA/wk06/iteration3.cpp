/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    int halfSize = lst.size() / 2;
    auto it = lst.begin();

    for (int i = 0; i < halfSize; ++i, ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

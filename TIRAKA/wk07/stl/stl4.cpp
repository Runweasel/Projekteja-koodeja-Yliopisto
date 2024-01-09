#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Return an iterator which points to the last even integer of the vector
 *        If the value is not found, return v.rend()
 *
 * @param v the vector to be scanned through
 * @return std::vector<int>::reverse_iterator
 */
std::vector<int>::reverse_iterator findLastEven(std::vector<int>& v)
{
    vector<int>::reverse_iterator it;

    // Vaihdetaan suunta reverse, ja lambda-funktiolla testataan tasalukua.
    // Palautetaan it jos se ei ole rend...

    it = find_if(v.rbegin(), v.rend(), [](int n) { return n % 2 == 0; });
    if (it != v.rend())
        return it;
    else
        return v.rend();
}


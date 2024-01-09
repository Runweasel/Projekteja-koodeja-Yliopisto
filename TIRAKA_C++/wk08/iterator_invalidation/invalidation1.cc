#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief creates a vector with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 */
std::vector<int> ascendingVector(int n) {

    // iteraattori osoittaa tyhjän vektorin alkuun, ja sitten yrittää
    // lisätä kohtaan missä olisi 'beg1 +1', joka ei toimi.
    std::vector<int> v;
    auto beg1 = v.begin();

    // lisätään numero vektorin loppuun iteraattorin osoittamaan kohtaan
    // ja lisätään +1, jotta iteraattori osoittaa seuraavaan kohtaan mihin lisätään.
    for (int i = 0; i < n; ++i) {
        beg1 = v.insert(beg1, i) + 1;
    }

    return v;
}


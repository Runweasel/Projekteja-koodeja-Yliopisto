#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>

/**
 * @brief creates a vector of integers with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 * @return std::vector<int>
 */

inline std::vector<int> ascendingVector(int n) {
    std::vector<int> v(n);
    return std::iota(v.begin(), v.end(), 0), v; // Täyttää vektorin luvuilla ja palauttaa sen
}

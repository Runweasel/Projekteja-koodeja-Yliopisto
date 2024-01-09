#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */

void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    using Iter = std::vector<int>::iterator;

    for (Iter it = vec.begin(); it != vec.end(); ) {
        if (*it % 2 == 0) {
            it = vec.insert(it, *it) + 2;  // Lisätään duplikaatit ja siirretään +2 eteenpäin, jotta päästään originaalin ja duplikaatin ohi
        } else {
            it = vec.erase(it);  // erase poistaa ja palauttaa iteraattorin seuraavaan
        }
    }
}

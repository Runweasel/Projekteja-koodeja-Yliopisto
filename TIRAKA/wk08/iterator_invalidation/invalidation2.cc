#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {

    // kun i iteraattori poistetaan niin i mitätöityy ja ei voida tehdä i + 2
    // korjataan se asettamalla it osoittamaan toiseen elementtiin
    // ja tarkistetaan onko lopussa. Jos ei ole, niin käytetään erase poistamaan
    // joka osoittaa suoraan heti seuraavaan elementtiin, jolloin saadaan joka toinen poistettua.

    for ( auto it = vec.begin(); it != vec.end(); ) {
        ++it;
        if (it != vec.end()) {
            it = vec.erase(it);
        }
    }

}


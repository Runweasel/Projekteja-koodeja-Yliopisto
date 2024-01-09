#include <iterator>
#include <map>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief From a map find the first element, whose value is at least given limit
 *        regardless of the key of the element. Return only the value or
 *        NOT_FOUND if none of the values match the the search criteria.
 * @param m map that is scanned trough
 * @param given limit for the values to search
 * @return int the real found value
 */
int findAtLeastGiven(std::map<std::string, int>& m, int given)
{
    // etsii mapista ensimmäisen alkion, joka täyttää annetun ehdon...

    auto it = find_if(m.begin(), m.end(), [ given ](const pair<string, int> &pari) {
        // lambda-funktio tarkistaa onko avain-arvo parin int arvo suurempi vai pienempi
        // kuin annettu given...

        return pari.second >= given;
    });

    if (it != m.end()) {
        return it->second;
    }

    return NOT_FOUND;
}


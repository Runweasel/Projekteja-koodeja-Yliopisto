#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Remove from vector v all elements with value less than the limit
 * @param v a vector whose values are to be erased if less than limit
 * @param limit a threshold whose lower values are removed
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int removeLessThan(std::vector<int>& v, int limit)
{

    // erase poistaa kaikki elementit remove_if palauttamasta iteraattorista vektorin
    // loppuun.
    // Eli ensiksi remove_if siirtää ei halutut ehdolliset loppuun ja sitten palauttaa iteraattorin,
    // joka osoittaa ensimmäiseen siirrettyyn. Sitten erase poistaa iteraattorin osoittaman ja lopun arvot.
    v.erase( remove_if(v.begin(), v.end(), [limit](int value) {
        // lambda-funktio testaa onko arvo pienempi kuin limit
        return value < limit;
            }), v.end());
    return EXIT_SUCCESS;

}


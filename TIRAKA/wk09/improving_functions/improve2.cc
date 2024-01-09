#include <iterator>
#include <vector>
#include <algorithm>


/**
 * @brief Gets the smallest value from the vector passed as a parameter.
 *
 * @param vec vector which is searched for the smallest value.
 * @return int - the smallest value or 0 (zero) if vector is empty.
 */
int minValue(const std::vector<int> vec){
    // Jos tyhjä niin palauta nolla
    if ( vec.empty() ) {
        return 0;
    }
    // min_element palauttaa pienimmän elementin. Ei tarvitse erikseen
    // järjestää.
    return *std::min_element(vec.begin(), vec.end());
}

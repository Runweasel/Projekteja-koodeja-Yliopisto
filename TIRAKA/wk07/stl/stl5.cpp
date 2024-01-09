#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    auto middle_one = stable_partition(v.begin(), v.end(), [](int n) {return n % 3 == 0; });

    auto middle_two = stable_partition(middle_one, v.end(), [](int n) {return n % 3 == 1; });

    // Jääneille arvoille jää 2 kun jakaa 3, joten ei tarvetta kolmannelle opetaariolle

    sort(v.begin(), middle_one);
    sort(middle_one, middle_two);
    sort(middle_two, v.end());

    return EXIT_SUCCESS;
}


#include <iterator>
#include <vector>
#include <algorithm>
#include <random>


//---- Some utilities
using iter = std::vector<int>::iterator;
using RNG = std::default_random_engine;

/**
 * @brief Sorts a given vector using a 3 part randomized quicksort algorithm.
 *        Randomization is used to avoid worst case (where the pivot value is
 *        chosen poorly).
 *
 * HINT: The way randomization is implemented can be changed. Shuffle may not
 *       be the only or the best way to implement randomization.
 *
 * @param begin an iterator that points to the beginning part of the sequence where the quicksort is performed.
 * @param end an iterator that points to the end part of the sequence where the quicksort is performed
 * @param rng the random number generator that can be used
 */

void randomizedThreePartQuicksort(iter begin, iter end, RNG& rng)
{
    if (begin == end) return;

    std::uniform_int_distribution<> dist(0, std::distance(begin, end) - 1);
    auto randomIndex = begin + dist(rng); // Valitse satunnainen indeksi alueelta.

    // Vaihdetaan satunnainen alkio ensimmäisen alkion kanssa. Tämä helpottaa pivot-elementtien käsittelyä osituksen aikana.
    std::iter_swap(begin, randomIndex);
    auto pivot = *begin;

    iter piemempi = begin;  // Osoittaa paikkaan, johon seuraava arvo, joka on pienempi kuin pivot, tulisi sijoittaa.
    iter suurempi = end;    // Osoittaa paikkaan, johon seuraava arvo, joka on suurempi kuin pivot, tulisi sijoittaa.
    iter i = begin;   // Parhaillaan tarkasteltava alkio.

    while (i < suurempi) {
        if (*i < pivot) {
            std::iter_swap(i, piemempi);
            ++piemempi;
            ++i;
        } else if (pivot < *i) {
            --suurempi;
            std::iter_swap(i, suurempi);
        } else {
            ++i;
        }
    }

    randomizedThreePartQuicksort(begin, piemempi, rng);
    randomizedThreePartQuicksort(suurempi, end, rng);
}

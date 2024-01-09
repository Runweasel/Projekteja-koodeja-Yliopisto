#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // Shufflaa sanan keskimmäiset kirjaimet

        if (word.size() > 2) {

            std::string middle = word.substr(1, word.size()-2);
            std::shuffle(middle.begin(), middle.end(), generator);
            word = word.front() + middle + word.back();
        }
        std::cout << word << std::endl;
    }
}

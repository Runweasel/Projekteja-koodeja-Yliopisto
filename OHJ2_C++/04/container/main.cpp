#include <cstdlib>
#include <iostream>
#include <vector>


// Prints the elements in the parameter vector ints.
void print_integers(const std::vector< int >& ints)
{
    for(auto elem : ints) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i) {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back( new_integer );
    }
}

// TODO: Implement your solution here

bool same_values(std::vector< int >& ints) {

    int eka = ints[0];
    for (unsigned long i = 1; i < ints.size(); i++) {
        if ( ints[i] != eka) {
            return false;
        }
    }
    return true;
}

bool is_ordered_non_strict_ascending(std::vector< int >& ints) {

    for (unsigned long i = 1; i < ints.size(); i++) {
        if( ints[i] < ints[i-1] ) {
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(std::vector< int >& ints) {

    int erotus = ints[1] - ints [0];

    for (unsigned long i = 1; i < ints.size(); i++) {
        if( ints[i] - ints[i-1] != erotus ) {
            return false;
        }
    }
    return true;
}
bool is_geometric_series(std::vector< int >& ints) {

    if ( ints[0] == 0 ) {
        return false;
    }

    int kerto = ints [1] / ints [0];

    for (unsigned long i = 1; i < ints.size(); i++) {
        if ( ints[i] != (ints[i-1] * kerto)) {
            return false;
        }
    }
    return true;
}

void triple_integers(std::vector< int >& ints) {

    for (unsigned long i = 0; i < ints.size(); i++) {
        ints[i] = ints[i] * 3;
    }
    return;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    if(how_many <= 0) {
        return EXIT_FAILURE;
    }

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers)) {
        std::cout << "All the integers are the same" << std::endl;
    } else {
        std::cout << "All the integers are not the same" << std::endl;
    }

    if(is_ordered_non_strict_ascending(integers)) {
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    } else {
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;
    }

    if(is_arithmetic_series(integers)) {
        std::cout << "The integers form an arithmetic series" << std::endl;
    } else {
        std::cout << "The integers do not form an arithmetic series" << std::endl;
    }

    if(is_geometric_series(integers)) {
        std::cout << "The integers form a geometric series" << std::endl;
    } else {
        std::cout << "The integers do not form a geometric series" << std::endl;
    }

    triple_integers(integers);
    std::cout << "Tripled values: ";
    print_integers(integers);

    return EXIT_SUCCESS;
}


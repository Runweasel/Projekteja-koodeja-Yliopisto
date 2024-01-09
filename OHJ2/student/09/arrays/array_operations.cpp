#include "array_operations.hh"

int greatest_v1(int* itemptr, int size) {
    int greatest = *itemptr;
    for (int i = 1; i < size; ++i) {
        if (*(itemptr + i) > greatest) {
            greatest = *(itemptr + i);
        }
    }
    return greatest;
}

int greatest_v2(int* itemptr, int* endptr) {
    int greatest = *itemptr;
    for (; itemptr != endptr; ++itemptr) {
        if (*itemptr > greatest) {
            greatest = *itemptr;
        }
    }
    return greatest;
}

void copy(int* itemptr, int* endptr, int* targetptr) {
    for (; itemptr != endptr; ++itemptr, ++targetptr) {
        *targetptr = *itemptr;
    }
}

void reverse(int* leftptr, int* rightptr) {
    --rightptr;
    while (leftptr < rightptr) {
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;
        ++leftptr;
        --rightptr;
    }
}

#include "include/vector.h"

DEFINE_VECTOR(int)

int main() {
    /* Create a vector of integers */
    Vector_int *v = vector_int_create(0);

    /* Destroy the vector */
    vector_int_destroy(v);
    return 0;
}
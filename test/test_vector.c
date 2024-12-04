#include "../include/vector.h"
/* Test vector functionality */
#include <stdbool.h>
#include <stdio.h>

typedef struct point {
    int x;
    int y;
} point;

void print_point(point p) {
    printf("Point{x: %d, y: %d}\n", p.x, p.y);
}

DEFINE_VECTOR(point)

// test creating vector
bool vector_create() {
    Vector_point *v = vector_point_create(0);
    vector_point_destroy(v);
    return true;
}

// test adding to vector
bool vector_add() {
    Vector_point *v = vector_point_create(0);
    printf("Before push back\n");
    point p1 = {1, 2};
    point p2 = {3, 4};
    point p3 = {5, 6};
    point p4 = {7, 8};
    vector_point_push_back(v, p1);
    vector_point_push_back(v, p2);
    vector_point_push_back(v, p3);
    vector_point_push_back(v, p4);
    point p = {5, 6};
    vector_point_push_back(v, p);
    if (vector_size(v) != 5) {
        return false;
    }
    vector_point_print(v, print_point);
    printf("After push back\n");

    // delete an element
    printf("Deleting element at index 1, 2\n");
    vector_point_delete(v, 1);
    vector_point_delete(v, 2);
    printf("Pop back last point\n");
    point popped_point = vector_point_pop_back(v);
    printf("Popped point: ");
    print_point(popped_point);
    if (vector_size(v) != 2) {
        return false;
    }
    vector_point_print(v, print_point);

    vector_point_destroy(v);
    return true;
}

int success() {
    printf("Test passed successfully\n");
    return 0;
}

int fail() {
    printf("Test failed\n");
    return 1;
}

int main() {
    return vector_create() && vector_add() ? success() : fail();
}

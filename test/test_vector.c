#include "../include/vector.h"
/* Test vector functionality */
#include <stdbool.h>
#include <stdio.h>

typedef struct point {
    int x;
    int y;
} point;

void print_point(point *p) {
    printf("Point{x: %d, y: %d}\n", p->x, p->y);
}

DEFINE_VECTOR(point)

// test creating vector
bool vector_create() {
    vector_point *v = vector_create_point(0);
    vector_destroy_point(v);
    return true;
}

// test adding to vector
bool vector_add() {
    vector_point *v = vector_create_point(0);
    printf("Before push back\n");
    point p1 = {1, 2};
    point p2 = {3, 4};
    point p3 = {5, 6};
    point p4 = {7, 8};
    vector_push_back_point(v, p1);
    vector_push_back_point(v, p2);
    vector_push_back_point(v, p3);
    vector_push_back_point(v, p4);
    point p = {9, 9};
    vector_push_back_point(v, p);
    if (vector_size_point(v) != 5) {
        return false;
    }
    vector_print_point(v, print_point);
    printf("After push back\n");

    // delete an element
    printf("Deleting element at index 1, 2\n");
    vector_delete_point(v, 1);
    vector_delete_point(v, 2);
    printf("Pop back last point\n");
    point *popped_point = vector_pop_back_point(v);
    printf("Popped point: ");
    print_point(popped_point);
    if (vector_size_point(v) != 2 || popped_point->x != 9 || popped_point->y != 9) {
        return false;
    }
    vector_print_point(v, print_point);

    vector_destroy_point(v);
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

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define VECTOR_INIT_CAPACITY 4

/* Macro to define a vector for a specific data type */
#define DEFINE_VECTOR(type) \
\
typedef struct { \
    type *data; \
    size_t size; \
    size_t capacity; \
} Vector_##type; \
\
/* Function to create a vector */ \
Vector_##type *vector_create_##type(size_t capacity) { \
    Vector_##type *vector = (Vector_##type *)malloc(sizeof(Vector_##type)); \
    if (!vector) { \
        perror("Failed to allocate vector"); \
        exit(EXIT_FAILURE); \
    } \
    vector->size = 0; \
    vector->capacity = capacity > 0 ? capacity : VECTOR_INIT_CAPACITY; \
    vector->data = (type *)malloc(sizeof(type) * vector->capacity); \
    if (!vector->data) { \
        perror("Failed to allocate vector data"); \
        free(vector); \
        exit(EXIT_FAILURE); \
    } \
    return vector; \
} \
\
/* Function to destroy the vector */ \
void vector_destroy_##type(Vector_##type *vector) { \
    if (vector) { \
        free(vector->data); \
        free(vector); \
    } \
} \
\
/* Function to add an element to the end */ \
void vector_push_back_##type(Vector_##type *vector, type value) { \
    if (vector->size == vector->capacity) { \
        vector->capacity *= 2; \
        type *temp = (type *)realloc(vector->data, sizeof(type) * vector->capacity); \
        if (!temp) { \
            perror("Failed to reallocate vector data"); \
            vector_destroy_##type(vector); \
            exit(EXIT_FAILURE); \
        } \
        vector->data = temp; \
    } \
    vector->data[vector->size++] = value; \
} \
\
/* Function to access an element by index */ \
type *vector_get_##type(Vector_##type *vector, size_t index) { \
    if (index >= vector->size) { \
        fprintf(stderr, "Index out of bounds \n"); \
        exit(EXIT_FAILURE); \
    } \
    return &vector->data[index]; \
} \
\
/* Function to delete an element by index */ \
void vector_delete_##type(Vector_##type *vector, size_t index) { \
    if (index >= vector->size) { \
        fprintf(stderr, "Index out of bounds \n"); \
        exit(EXIT_FAILURE); \
    } \
    memmove(&vector->data[index], &vector->data[index + 1], \
            sizeof(type) * (vector->size - index - 1)); \
    vector->size--; \
    /* Shrink capacity */ \
    if (vector->size > 0 && vector->size == vector->capacity / 4) { \
        vector->capacity /= 2; \
        type *temp = (type *)realloc(vector->data, sizeof(type) * vector->capacity); \
        if (!temp) { \
            perror("Failed to reallocate vector data"); \
            vector_destroy_##type(vector); \
            exit(EXIT_FAILURE); \
        } \
        vector->data = temp; \
    } \
} \
\
/* Function to pop last element and return it */ \
type *vector_pop_back_##type(Vector_##type *vector) { \
    if (vector->size == 0) { \
        fprintf(stderr, "Vector is empty \n"); \
        exit(EXIT_FAILURE); \
    } \
    /* Optionally shrink capacity */ \
    if (vector->size > 0 && vector->size == vector->capacity / 4) { \
        vector->capacity /= 2; \
        type *temp = (type *)realloc(vector->data, sizeof(type) * vector->capacity); \
        if (!temp) { \
            perror("Failed to reallocate vector data"); \
            vector_destroy_##type(vector); \
            exit(EXIT_FAILURE); \
        } \
        vector->data = temp; \
    } \
    type *value = vector_get_##type(vector, vector->size - 1); \
    --vector->size; \
    return value; \
} \
\
/* Function to check if the vector is empty */ \
bool vector_is_empty_##type(Vector_##type *vector) { \
    return vector->size == 0; \
} \
\
/* Function to get the size of the vector */ \
size_t vector_size_##type(Vector_##type *vector) { \
    return vector->size; \
} \
\
/* Function to get the capacity of the vector */ \
size_t vector_capacity_##type(Vector_##type *vector) { \
    return vector->capacity; \
} \
/* Function to remove all elements from the vector */ \
void vector_clear_##type(Vector_##type *vector) { \
    vector->size = 0; \
    /* Optionally reset capacity */ \
    vector->capacity = VECTOR_INIT_CAPACITY; \
    type *temp = (type *)realloc(vector->data, sizeof(type) * vector->capacity); \
    if (!temp) { \
        perror("Failed to reallocate vector data"); \
        vector_destroy_##type(vector); \
        exit(EXIT_FAILURE); \
    } \
    vector->data = temp; \
} \
\
/* Function to print the vector and its elements */ \
void vector_print_##type(Vector_##type *vector, void (*print_func)(type *)) { \
    printf("Vector{size=%zu, capacity=%zu}\n", vector->size, vector->capacity); \
    printf("Vector of %s elements:\n", #type); \
    for (size_t i = 0; i < vector->size; i++) { \
        printf("    [%zu] ", i); \
        print_func(&vector->data[i]); \
    } \
}

#endif /* VECTOR_H */

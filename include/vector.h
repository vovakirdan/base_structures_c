#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Vector_##type *vector_##type##_create(size_t capacity) { \
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
void vector_##type##_destroy(Vector_##type *vector) { \
    if (vector) { \
        free(vector->data); \
        free(vector); \
    } \
} \
\
/* Function to add an element to the end */ \
void vector_##type##_push_back(Vector_##type *vector, type value) { \
    if (vector->size == vector->capacity) { \
        vector->capacity *= 2; \
        type *temp = (type *)realloc(vector->data, sizeof(type) * vector->capacity); \
        if (!temp) { \
            perror("Failed to reallocate vector data"); \
            vector_##type##_destroy(vector); \
            exit(EXIT_FAILURE); \
        } \
        vector->data = temp; \
    } \
    vector->data[vector->size++] = value; \
} \
\
/* Function to access an element by index */ \
type *vector_##type##_get(Vector_##type *vector, size_t index) { \
    if (index >= vector->size) { \
        fprintf(stderr, "Index out of bounds \n"); \
        exit(EXIT_FAILURE); \
    } \
    return &vector->data[index]; \
} \
\
/* Function to delete an element by index */ \
void vector_##type##_delete(Vector_##type *vector, size_t index) { \
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
            vector_##type##_destroy(vector); \
            exit(EXIT_FAILURE); \
        } \
        vector->data = temp; \
    } \
} \
\
/* Function to pop last element and return it */ \
type *vector_##type##_pop_back(Vector_##type *vector) { \
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
            vector_##type##_destroy(vector); \
            exit(EXIT_FAILURE); \
        } \
        vector->data = temp; \
    } \
    type *value = vector_##type##_get(vector, vector->size - 1); \
    --vector->size; \
    return value; \
} \
\
/* Function to get the size of the vector */ \
size_t vector_size(Vector_##type *vector) { \
    return vector->size; \
} \
\
/* Function to get the capacity of the vector */ \
size_t vector_capacity(Vector_##type *vector) { \
    return vector->capacity; \
} \
\
/* Function to print the vector and its elements */ \
void vector_##type##_print(Vector_##type *vector, void (*print_func)(type *)) { \
    printf("Vector{size=%zu, capacity=%zu}\n", vector->size, vector->capacity); \
    printf("Vector of %s elements:\n", #type); \
    for (size_t i = 0; i < vector->size; i++) { \
        printf("    [%zu] ", i); \
        print_func(&vector->data[i]); \
    } \
}

#endif /* VECTOR_H */

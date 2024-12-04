#ifndef DICT_H
#define DICT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Initial size of the hash table */
#define DICT_INITIAL_CAPACITY 16

/* Hash function for const char * */
static size_t str_hash(const char *key) {
    size_t hash = 5381;
    int c;
    while ((c = (unsigned char)*key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

/* Equality function for const char * */
static int str_equals(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

/* Macro to define a dictionary for a specific value type */
#define DEFINE_DICT(ValueType) \
\
typedef struct dict_entry_##ValueType { \
    const char *key; \
    ValueType value; \
    struct dict_entry_##ValueType *next; \
} dict_entry_##ValueType; \
\
typedef struct { \
    dict_entry_##ValueType **buckets; \
    size_t capacity; \
    size_t size; \
} dict_##ValueType; \
\
/* Implementations */ \
dict_##ValueType *dict_create_##ValueType(size_t capacity) { \
    dict_##ValueType *d = (dict_##ValueType *)malloc(sizeof(dict_##ValueType)); \
    if (!d) { \
        perror("Failed to allocate dictionary"); \
        exit(EXIT_FAILURE); \
    } \
    d->capacity = capacity > 0 ? capacity : DICT_INITIAL_CAPACITY; \
    d->size = 0; \
    d->buckets = (dict_entry_##ValueType **)calloc(d->capacity, sizeof(dict_entry_##ValueType *)); \
    if (!d->buckets) { \
        perror("Failed to allocate buckets"); \
        free(d); \
        exit(EXIT_FAILURE); \
    } \
    return d; \
} \
void dict_destroy_##ValueType(dict_##ValueType *d) { \
    if (d) { \
        for (size_t i = 0; i < d->capacity; i++) { \
            dict_entry_##ValueType *entry = d->buckets[i]; \
            while (entry) { \
                dict_entry_##ValueType *temp = entry; \
                entry = entry->next; \
                free(temp); \
            } \
        } \
        free(d->buckets); \
        free(d); \
    } \
} \
void dict_insert_##ValueType(dict_##ValueType *d, const char *key, ValueType value) { \
    size_t index = str_hash(key) % d->capacity; \
    dict_entry_##ValueType *entry = d->buckets[index]; \
    while (entry) { \
        if (str_equals(entry->key, key)) { \
            entry->value = value; \
            return; \
        } \
        entry = entry->next; \
    } \
    dict_entry_##ValueType *new_entry = (dict_entry_##ValueType *)malloc(sizeof(dict_entry_##ValueType)); \
    if (!new_entry) { \
        perror("Failed to allocate dictionary entry"); \
        exit(EXIT_FAILURE); \
    } \
    new_entry->key = key; \
    new_entry->value = value; \
    new_entry->next = d->buckets[index]; \
    d->buckets[index] = new_entry; \
    d->size++; \
} \
ValueType *dict_get_##ValueType(dict_##ValueType *d, const char *key) { \
    size_t index = str_hash(key) % d->capacity; \
    dict_entry_##ValueType *entry = d->buckets[index]; \
    while (entry) { \
        if (str_equals(entry->key, key)) { \
            return &entry->value; \
        } \
        entry = entry->next; \
    } \
    return NULL; \
} \
int dict_delete_##ValueType(dict_##ValueType *d, const char *key) { \
    size_t index = str_hash(key) % d->capacity; \
    dict_entry_##ValueType *entry = d->buckets[index]; \
    dict_entry_##ValueType *prev = NULL; \
    while (entry) { \
        if (str_equals(entry->key, key)) { \
            if (prev) { \
                prev->next = entry->next; \
            } else { \
                d->buckets[index] = entry->next; \
            } \
            free(entry); \
            d->size--; \
            return 1; \
        } \
        prev = entry; \
        entry = entry->next; \
    } \
    return 0; \
} \
int dict_is_empty_##ValueType(dict_##ValueType *d) { \
    return d->size == 0; \
} \
size_t dict_size_##ValueType(dict_##ValueType *d) { \
    return d->size; \
}

#endif /* DICT_H */

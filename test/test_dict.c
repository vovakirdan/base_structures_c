#include "../include/dict.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct SomeStruct {
    int *arr;
    double val;
} SomeStruct;

DEFINE_DICT(SomeStruct)

bool dict_operations() {
    dict_SomeStruct *d = dict_create_SomeStruct(0);  // creates default size cap
    int arr1[3] = {1, 2, 3}; int arr2[3] = {4, 5, 6};
    SomeStruct struct1 = {arr1, 1.0};
    SomeStruct struct2 = {arr2, 2.0};

    dict_insert_SomeStruct(d, "first", struct1);
    dict_insert_SomeStruct(d, "second", struct2);

    SomeStruct *s1 = dict_get_SomeStruct(d, "first");
    SomeStruct *s2 = dict_get_SomeStruct(d, "second");

    printf("s1: %d %d %d\n", s1->arr[0], s1->arr[1], s1->arr[2]);
    printf("s2: %d %d %d\n", s2->arr[0], s2->arr[1], s2->arr[2]);

    dict_destroy_SomeStruct(d);

    return true;
}

int main() {
    return (int)dict_operations();
}

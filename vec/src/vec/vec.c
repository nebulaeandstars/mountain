#include "vec.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Returns an empty Vec.
 */
Vec vec_new(VecElementType type)
{
    Vec vec;
    vec.data      = malloc(0);
    vec.elem_type = type;
    vec.size      = 0;
    vec.capacity  = 0;

    return vec;
}

/**
 * Returns a new Vec with the given capacity.
 */
Vec vec_with_capacity(VecElementType type, size_t capacity)
{
    Vec vec = vec_new(type);
    vec_realloc(&vec, capacity);
    return vec;
}

/**
 * Frees the contents of a given Vec.
 */
void vec_destroy(Vec* vec)
{
    free(vec->data);
    vec->data = NULL;
}

/**
 * Grows a given Vec.
 *
 * - An empty Vec will be reallocated to 4 bytes.
 * - A 4-byte Vec will be reallocated to 16 bytes.
 * - Any other Vec will be reallocated to 2 * its old capacity.
 */
void vec_grow(Vec* vec)
{
    size_t current_capacity = vec->capacity;
    size_t target_capacity;

    if (current_capacity == 0)
        target_capacity = 4;
    else if (current_capacity == 4)
        target_capacity = 16;
    else
        target_capacity = 2 * current_capacity;

    vec_realloc(vec, target_capacity);
}

/**
 * Grows or shrinks a Vec to a given capacity.
 */
void vec_realloc(Vec* vec, size_t capacity)
{
    // Reallocate *data to to the desired capacity,
    void* p = realloc(vec->data, capacity * vec_get_elem_size(vec));
    if (p == NULL) {
        printf("Vec %p failed to reallocate.", vec->data);
        exit(1);
    }
    vec->data = p;

    // then update the internal capacity to match, truncating if necessary.
    vec->capacity = capacity;
    if (vec->size > vec->capacity) {
        vec->size = vec->capacity;
    }
}

/**
 * Appends a single element to the end of the Vec.
 */
void vec_push_elem(Vec* vec, void* elem)
{
    // Grow the Vec if necessary,
    if (++vec->size >= vec->capacity) {
        vec_grow(vec);
    }

    // then update the value at the corresponding index.
    void* ref = vec_get_ref(vec, vec->size - 1);
    switch (vec->elem_type) {
        case VEC_U8:
            *(uint8_t*)ref = *(uint8_t*)elem;
            break;
        case VEC_U16:
            *(uint16_t*)ref = *(uint16_t*)elem;
            break;
        case VEC_U32:
            *(uint32_t*)ref = *(uint32_t*)elem;
            break;
        case VEC_U64:
            *(uint64_t*)ref = *(uint64_t*)elem;
            break;
        default:
            printf("Unknown VecElementType in vec_push_elem()!");
            exit(1);
    }
}

/**
 * Get a reference to the element at a given index.
 */
void* vec_get_ref(Vec* vec, size_t index)
{
    // If the element shouldn't exist, panic.
    if (index >= vec->size) {
        fprintf(stderr, "Vec: index %ld is out of bounds! (size: %ld)\n", index,
                vec->size);
        exit(1);
    }

    // otherwise, return a reference to it.
    return vec->data + (vec_get_elem_size(vec) * index);
}

/**
 * Prints the contents of the Vec to stdout.
 */
void vec_display(Vec* vec)
{
    putchar('[');
    for (int i = 0; i < vec->size; i++) {
        switch (vec->elem_type) {
            case VEC_U8:
                printf("%d", *(uint8_t*)vec_get_ref(vec, i));
                break;
            case VEC_U16:
                printf("%d", *(uint16_t*)vec_get_ref(vec, i));
                break;
            case VEC_U32:
                printf("%d", *(uint32_t*)vec_get_ref(vec, i));
                break;
            case VEC_U64:
                printf("%ld", *(uint64_t*)vec_get_ref(vec, i));
                break;
            default:
                printf("Unknown VecElementType in vec_display()!");
                exit(1);
        }
        if (i < vec->size - 1) {
            putchar(',');
        }
    }
    printf("]\n");
}

/**
 * Returns the size of a Vec's elements in bytes.
 */
size_t vec_get_elem_size(Vec* vec)
{
    switch (vec->elem_type) {
        case VEC_U8:
            return 1;
        case VEC_U16:
            return 2;
        case VEC_U32:
            return 4;
        case VEC_U64:
            return 8;
        default:
            printf("Unknown VecElementType in vec_elem_size()!");
            exit(1);
    }
}

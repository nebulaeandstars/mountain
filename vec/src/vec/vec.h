#include <stdint.h>
#include <stdio.h>

typedef enum VecElementType {
    VEC_U8,
    VEC_U16,
    VEC_U32,
    VEC_U64,
} VecElementType;

/**
 * An interface that wraps a dynamically-sized array of any VecElementType.
 *
 * size_t size => The size of the array (ie. current number of elements)
 *
 * size_t capacity => The total capacity of the array.
 *   - memory reallocations only happen when the capacity grows, or when the
 *     size is >= the capacity.
 *
 * void *data => A pointer to the start of the array.
 */
typedef struct Vec {
    VecElementType elem_type;
    size_t size;
    size_t capacity;
    void* data;
} Vec;

// --------------------
// ----- creation -----
// --------------------

/**
 * Returns an empty Vec.
 */
Vec vec_new(VecElementType type);

/**
 * Returns a new Vec with the given capacity.
 */
Vec vec_with_capacity(VecElementType type, size_t capacity);

/**
 * Frees the contents of a given Vec.
 */
void vec_destroy(Vec* vec);

// ------------------------
// ----- reallocation -----
// ------------------------

/**
 * Grows a given Vec.
 *
 * - An empty Vec will be reallocated to 4 bytes.
 * - A 4-byte Vec will be reallocated to 16 bytes.
 * - Any other Vec will be reallocated to 2 * its old capacity.
 */
void vec_grow(Vec* vec);

/**
 * Grows or shrinks a Vec to a given capacity.
 */
void vec_realloc(Vec* vec, size_t capacity);

// ------------------------
// ----- manipulation -----
// ------------------------

/**
 * Appends a single element to the end of the Vec.
 */
void vec_push_elem(Vec* vec, void* c);

// ----------------
// ----- info -----
// ----------------

/**
 * Get a reference to the element at a given index.
 */
void* vec_get_ref(Vec* vec, size_t index);

/**
 * Returns the size of a Vec's elements in bytes.
 */
size_t vec_get_elem_size(Vec* vec);

/**
 * Prints the contents of the Vec to stdout.
 *
 * The format will look something like "[0,307,81]\n"
 */
void vec_display(Vec* vec);

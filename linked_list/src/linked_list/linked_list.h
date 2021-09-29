#include <stdio.h>

typedef enum ListElementType {
    LIST_U8,
    LIST_U16,
    LIST_U32,
    LIST_U64,
} ListElementType;

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    void* value;
} Node;

typedef struct LinkedList {
    ListElementType elem_type;
    size_t* len;
    Node* first;
} LinkedList;

// --------------------
// ----- creation -----
// --------------------

/**
 * Creates an empty LinkedList.
 */
LinkedList list_new();

/**
 * Frees all nodes in a given LinkedList.
 */
void list_destroy();

// ------------------------
// ----- manipulation -----
// ------------------------

/**
 * Pushes a value to the front of the list.
 */
void list_push(LinkedList* list, void* val);

/**
 * Pushes a value to the end of the list.
 */
void list_push_end(LinkedList* list, void* val);

/**
 * Pops a Node off the front of the list.
 * The whole Node must be freed manually to prevent a memory leak.
 */
Node* list_pop(LinkedList* list);

/**
 * Pops a Node off the end of the list.
 * The whole Node must be freed manually to prevent a memory leak.
 */
Node* list_pop_end(LinkedList* list);

// ----------------
// ----- info -----
// ----------------

/**
 * Returns the length of the list.
 */
int list_length(LinkedList* list);

/**
 * Prints the contents of the list to stdout.
 */
void list_display(LinkedList* list);

/**
 * Returns the size of a LinkedList's elements in bytes.
 */
size_t list_get_elem_size(LinkedList* list);

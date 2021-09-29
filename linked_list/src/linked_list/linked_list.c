#include "linked_list.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Creates a new Node*. Panics if NULL.
 */
Node* node_new(LinkedList* list, void* value, Node* prev, Node* next)
{
    Node* node = malloc(sizeof(Node) + list_get_elem_size(list));
    if (node) {

        switch (list->elem_type) {
            case LIST_U8:
                *(uint8_t*)&node->value = *(uint8_t*)value;
                break;
            case LIST_U16:
                *(uint16_t*)&node->value = *(uint16_t*)value;
                break;
            case LIST_U32:
                *(uint32_t*)&node->value = *(uint32_t*)value;
                break;
            case LIST_U64:
                *(uint64_t*)&node->value = *(uint64_t*)value;
                break;
            default:
                printf("Unknown VecElementType in vec_push_elem()!");
                exit(1);
        }

        node->prev = prev;
        node->next = next;

        return node;
    }
    else {
        fprintf(stderr, "Node: failed to allocate!");
        exit(1);
    }
}

void node_destroy(Node* node)
{
    if (node->next)
        node_destroy(node->next);
    free(node);
}

LinkedList list_new()
{
    LinkedList list;
    list.elem_type = LIST_U8;
    list.len       = 0;
    list.first     = NULL;

    return list;
}

void list_destroy(LinkedList* list)
{
    if (list->first)
        node_destroy(list->first);
    list->first = NULL;
}

/**
 * Pushes a value to the front of the list.
 */
void list_push(LinkedList* list, void* val)
{
    // Create a new Node pointing to the current head.
    Node* new_first = node_new(list, val, NULL, list->first);

    // Then, update the list and old head to point to the new value.
    if (list->first)
        list->first->prev = new_first;

    list->first = new_first;
    list->len += 1;
}

/**
 * Pushes a value to the end of the list.
 */
void list_push_end(LinkedList* list, void* val)
{
    Node* new = node_new(list, val, NULL, NULL);

    Node* node = list->first;
    if (!node) {
        node = new;
        return;
    }

    while (node->next)
        node = node->next;
    node->next = new;
    new->prev  = node;

    list->len += 1;
    return;
}

/**
 * Pops a node off the front of the list.
 * The whole Node must be freed manually to prevent a memory leak.
 */
Node* list_pop(LinkedList* list)
{
    Node* node = list->first;

    if (node) {
        list->first = node->next;
        if (list->first)
            list->first->prev = NULL;
    }

    return node;
}

/**
 * Pops a node off the end of the list.
 * The whole Node must be freed manually to prevent a memory leak.
 */
Node* list_pop_end(LinkedList* list)
{
    Node* node = list->first;
    if (!node)
        return NULL;

    while (node->next)
        node = node->next;

    if (node->prev)
        node->prev->next = NULL;

    return node;
}

/**
 * Returns the length of the list.
 */
int list_length(LinkedList* list)
{
    int count = 0;
    for (Node* node = list->first; node != NULL; node = node->next) {
        count++;
    }
    return count;
}

/**
 * Prints the contents of the list to stdout.
 */
void list_display(LinkedList* list)
{
    printf("[");
    Node* node = list->first;
    while (node != NULL) {
        switch (list->elem_type) {
            case LIST_U8:
                printf("%d", *(uint8_t*)&node->value);
                break;
            case LIST_U16:
                printf("%d", *(uint16_t*)&node->value);
                break;
            case LIST_U32:
                printf("%d", *(uint32_t*)&node->value);
                break;
            case LIST_U64:
                printf("%ld", *(uint64_t*)&node->value);
                break;
            default:
                printf("Unknown VecElementType in vec_display()!");
                exit(1);
        }

        if (node->next) {
            putchar(',');
        }
        node = node->next;
    }
    printf("]");
}

/**
 * Returns the size of a LinkedList's elements in bytes.
 */
size_t list_get_elem_size(LinkedList* list)
{
    switch (list->elem_type) {
        case LIST_U8:
            return 1;
        case LIST_U16:
            return 2;
        case LIST_U32:
            return 4;
        case LIST_U64:
            return 8;
        default:
            printf("Unknown element type in list_get_elem_size()!");
            exit(1);
    }
}

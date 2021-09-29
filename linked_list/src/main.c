#include "linked_list.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // example: creating & displaying
    LinkedList list = list_new();

    printf("created new list");
    list_display(&list);
    printf("\n\n");

    // example: pushing
    {
        uint8_t chars[6] = {1, 2, 3, 4, 5, 6};
        printf("pushed 1 to the front of the list\n");
        list_push(&list, (void*)&chars[0]);
        printf("pushed 2 to the front of the list\n");
        list_push(&list, (void*)&chars[1]);
        printf("pushed 3 to the front of the list\n");
        list_push(&list, (void*)&chars[2]);

        list_display(&list);
        printf("\n\n");

        printf("pushed 4 to the end of the list\n");
        list_push_end(&list, (void*)&chars[3]);
        printf("pushed 5 to the end of the list\n");
        list_push_end(&list, (void*)&chars[4]);
        printf("pushed 6 to the end of the list\n");
        list_push_end(&list, (void*)&chars[5]);

        list_display(&list);
        printf("\n\n");
    }

    // example: popping
    {
        Node* node  = list_pop(&list);
        uint8_t val = *(uint8_t*)&node->value;
        printf("popped %d off the front of the list\n", val);
        list_display(&list);
        free(node);
        printf("\n\n");
    }
    {
        Node* node  = list_pop_end(&list);
        uint8_t val = *(uint8_t*)&node->value;
        printf("popped %d off the end of the list\n", val);
        list_display(&list);
        free(node);
        printf("\n\n");
    }

    // example: info
    printf("final length: %d\n", list_length(&list));

    // example: cleaning up
    list_destroy(&list);
}

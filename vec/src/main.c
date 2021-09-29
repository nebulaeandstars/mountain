#include "vec.h"

int main()
{
    {
        printf("Vec of u8: \n");
        Vec vec = vec_new(VEC_U8);

        uint8_t chars[4] = {'a', 'b', 'c', '\0'};
        vec_push_elem(&vec, (void*)&chars[0]);
        vec_push_elem(&vec, (void*)&chars[1]);
        vec_push_elem(&vec, (void*)&chars[2]);
        vec_push_elem(&vec, (void*)&chars[3]);
        vec_display(&vec);
        printf("as string:\n%s\n", (char*)vec.data);
        vec_destroy(&vec);
    }
    putchar('\n');
    {
        printf("Vec of u64: \n");
        Vec vec = vec_new(VEC_U64);

        uint64_t nums[3] = {100, 1000, 10000};
        vec_push_elem(&vec, (void*)&nums[0]);
        vec_push_elem(&vec, (void*)&nums[1]);
        vec_push_elem(&vec, (void*)&nums[2]);
        vec_display(&vec);

        printf("\nTrying to access an invalid address will panic: \n");
        vec_get_ref(&vec, 3);

        vec_destroy(&vec);
    }
}

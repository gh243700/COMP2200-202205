#include "parentheses.h"

#define PARENTHESES_MAX_SIZE (50)

/*
void malloc_push (char* pa_stack, char start, size_t *stack_item_count, size_t index)
char malloc_pop (char* pa_stack, size_t* index);
cd C:\Users\gh243\OneDrive - NPHI\Documents\GitHub\COMP2200\Lab8
clang -std=c89 -W -Wall -pedantic-errors *.c
*/


int main(void)
{
    {
        char* pa_stack;
        size_t size = 8;
        size_t index = 0;
        char* ptr;
        printf("---------------------------------------\n test start\n---------------------------------------");

        pa_stack = malloc(size * sizeof(char));
        
        printf("\nssss\n");
        malloc_push(&pa_stack, '{', &size, index++);
        assert(pa_stack[0] = '{');
        assert(size == 8);
        printf("ssss\n");
        malloc_push(&pa_stack, '[', &size, index++);
        assert(pa_stack[1] = '[');
        assert(size == 8);
        printf("ssss\n");
        malloc_push(&pa_stack, '(', &size, index++);
        assert(pa_stack[2] = '(');
        assert(size == 8);
        
        malloc_push(&pa_stack, 'a', &size, index++);
        assert(pa_stack[3] = 'a');
        assert(size == 8);
        
        malloc_push(&pa_stack, 'b', &size, index++);
        assert(pa_stack[4] = 'b');
        assert(size == 8);
        
        malloc_push(&pa_stack, 'c', &size, index++);
        assert(pa_stack[5] = 'c');
        assert(size == 8);
        
        
        malloc_push(&pa_stack, 'd', &size, index++);
        assert(pa_stack[7] = 'd');
        assert(size == 8);
        
        malloc_push(&pa_stack, 'e', &size, index++);
        assert(pa_stack[7] = 'e');
        assert(size == 8);
        printf("%p\n", (void*)pa_stack);
        malloc_push(&pa_stack, 'f', &size, index++);
        assert(pa_stack[8] = 'f');
        assert(size == 16);
        printf("%p\n", (void*)pa_stack);
        
        
        printf("---------------------------------------\n test1 fin\n---------------------------------------\n");
        printf("---------------------------------------\n start test2\n---------------------------------------\n");
        printf("%d\n", index);
        assert(pop(pa_stack, index--) == 'f');
        printf("%d\n", index);
        assert(pop(pa_stack, index--) == 'e');
        assert(pop(pa_stack, index--) == 'd');
        assert(pop(pa_stack, index--) == 'c');
        pop(pa_stack, index--);
        pop(pa_stack, index--);
        pop(pa_stack, index--);
        pop(pa_stack, index--);
        printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa \n %d", index);
        pop(pa_stack, index--);
        
        printf("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
        
        printf("---------------------------------------\n test2 fin\n---------------------------------------\n");
        free(pa_stack);
    }
    
    
    {
parenthesis_t parentheses[PARENTHESES_MAX_SIZE];

    size_t len = get_matching_parentheses(parentheses, PARENTHESES_MAX_SIZE, "}{)(][><");

    assert(len == 0);

    len = get_matching_parentheses(parentheses, PARENTHESES_MAX_SIZE, "{{{}}}");

    assert(len == 3);

    assert(parentheses[0].opening_index == 0);
    assert(parentheses[0].closing_index == 5);

    assert(parentheses[1].opening_index == 1);
    assert(parentheses[1].closing_index == 4);

    assert(parentheses[2].opening_index == 2);
    assert(parentheses[2].closing_index == 3);
    
    printf("----------------------------------------------------------------------------------\n");

    len = get_matching_parentheses(parentheses, PARENTHESES_MAX_SIZE, " {]}[[i]{)))} ]");
    printf("%d\n", len);
    assert(len == 4);

    assert(parentheses[0].opening_index == 1);
    assert(parentheses[0].closing_index == 3);

    assert(parentheses[1].opening_index == 4);
    assert(parentheses[1].closing_index == 14);

    assert(parentheses[2].opening_index == 5);
    assert(parentheses[2].closing_index == 7);

    assert(parentheses[3].opening_index == 8);
    assert(parentheses[3].closing_index == 12);

    len = get_matching_parentheses(parentheses, PARENTHESES_MAX_SIZE, "{this}(bracket;[](){[(><>)");

    assert(len == 5);

    assert(parentheses[0].opening_index == 0);
    assert(parentheses[0].closing_index == 5);

    assert(parentheses[1].opening_index == 15);
    assert(parentheses[1].closing_index == 16);

    assert(parentheses[2].opening_index == 17);
    assert(parentheses[2].closing_index == 18);

    assert(parentheses[3].opening_index == 21);
    assert(parentheses[3].closing_index == 25);

    assert(parentheses[4].opening_index == 23);
    assert(parentheses[4].closing_index == 24);
        
    printf("---------------------------------------\n test3 fin\n---------------------------------------\n");
    }
    
    
    {
        
        parenthesis_t parentheses[50];
        size_t len = get_matching_parentheses(parentheses, 3, "(({()))}");

        printf("---------------------------------------\n test4 start\n---------------------------------------\nlen:%d\n",len);
        
        assert(len == 3);

        assert(parentheses[0].opening_index == 0);
        assert(parentheses[0].closing_index == 6);

        assert(parentheses[1].opening_index == 1);
        assert(parentheses[1].closing_index == 5);

        assert(parentheses[2].opening_index == 2);
        assert(parentheses[2].closing_index == 7);

        printf("---------------------------------------\n test4 fin\n---------------------------------------\n");
        
    }
    
    return 0;
}

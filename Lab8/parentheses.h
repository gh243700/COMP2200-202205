#ifndef PARENTHESES_H
#define PARENTHESES_H

#include <assert.h>
#include <stdlib.h>
typedef struct {
    size_t opening_index;
    size_t closing_index;
} parenthesis_t;

size_t get_matching_parentheses(parenthesis_t* out_parentheses, size_t max_size, const char* str);




void malloc_push(char** pa_stack, char start, size_t* stack_item_count, size_t index);
void malloc_push_position(size_t** pa_stack_index, size_t start, size_t* stack_item_count, size_t index);
size_t pop_position(size_t* pa_stack_index, size_t index);
char pop(char* pa_stack, size_t index);
#endif /* PARENTHESES_H */

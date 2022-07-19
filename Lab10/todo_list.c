#include "todo_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t* pa_list = malloc(sizeof(todo_list_t));
    pa_list -> node = malloc(sizeof(node_t**));
    *(pa_list -> node) = NULL;
    pa_list -> count = 0;
    pa_list -> max_size = max_size;
    pa_list -> p = pa_list;

    return *pa_list;
}

void finalize_todo_list(todo_list_t* todo_list)
{
    node_t** pa_list_pp = todo_list -> node;
    node_t* pa_list_p = *(pa_list_pp);
    node_t* pa_list_next_p;
    
    while (pa_list_p != NULL) {
        free(pa_list_p -> task);
        pa_list_next_p = pa_list_p -> next;
        free(pa_list_p);
        pa_list_p = pa_list_next_p;
    }
    free(todo_list -> p);
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    node_t** pa_node_pp = todo_list -> node;
    node_t* node_p;
    node_t* pa_new_node;
    size_t task_len;

    if (todo_list -> count >= todo_list -> max_size) {
        return false;
    }
    
    pa_new_node = malloc(sizeof(node_t));
    task_len = strlen(task);
    pa_new_node -> task = malloc(sizeof(char) * task_len + 1);
    memcpy(pa_new_node -> task, task, sizeof(char) * task_len + 1);
    pa_new_node -> priority = priority;    

    if (*pa_node_pp == NULL) {
        pa_new_node -> next = NULL;
        *pa_node_pp = pa_new_node;
        goto exit_add;
    }

    node_t* p = NULL;
    node_p = *pa_node_pp;
    
    while (node_p != NULL) {
        if (node_p -> priority < priority) {
            break;
        }
        p = node_p;
        node_p = node_p -> next;
    }

    if (p == NULL) {
        pa_new_node -> next = *pa_node_pp;
        *pa_node_pp = pa_new_node;
    } else {
        pa_new_node -> next = node_p;
        p -> next = pa_new_node;
    }

exit_add:
    todo_list -> count = todo_list -> count + 1;
    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    node_t* pa_node;
    node_t* pa_node_next;
    if (is_empty(todo_list) == true) {
        return false;
    }

    pa_node = *(todo_list -> node);
    free(pa_node -> task); 
    pa_node_next = pa_node -> next;
    free(pa_node);
    *(todo_list -> node) = pa_node_next;
    todo_list -> count = todo_list -> count - 1;

    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    return (is_empty(todo_list) == true) ? NULL : (*(todo_list -> node)) -> task;
}

size_t get_count(const todo_list_t* todo_list)
{
    return todo_list -> count;
}

bool is_empty(const todo_list_t* todo_list)
{
    return *(todo_list -> node) == NULL;
}




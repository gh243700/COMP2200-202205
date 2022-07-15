#ifndef NODE_H
#define NODE_H

typedef struct node {
    char* key;
    int value;
    size_t key_len;
    struct node* next;
} node_t;

#endif /* NODE_H */

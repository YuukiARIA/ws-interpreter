#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

typedef struct tree_t *TREE;
typedef void (*ACTION)(void);

TREE tree_new(void);
TREE tree_delete(TREE tree);

#endif


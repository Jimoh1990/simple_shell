#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/**
 * struct Node - this represents a single node in a
 * linked list
 *
 * @var: the name of the node
 * @val: the value associated with this node
 * @next: a pointer the next node, this would be null if theres no next node.
 */
struct Node
{
	char *var;
	char *val;
	struct Node *next;
};

/* alias for struct Node */
typedef struct Node node;

size_t listlen(node *head);
void print_list(node *head);
node *add_node(node **head, const char *var, const char *val);
node *add_node_end(node **head, const char *var, const char *val);
void free_list(node *head);
node *get_tail(node *head);
node *get_node(node *head, const char *var);
bool delete_node(node **head, const char *var);
node *from_strarr(char **array);
char **to_strarr(node *head);
node *set_node(node **head, const char *var, const char *val);
node *set_default(node **head, const char *var, const char *val);

#endif

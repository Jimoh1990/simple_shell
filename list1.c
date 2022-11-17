#include "shell.h"

/**
 * print_list - prints all nodes in a linked list in this format
 * -> VAR=VAL
 *
 * @head: the head of the linked list
 * @quote: checks if its env or alias to be printed
 * Return: nothing
 */
void print_list(node *head, bool quote)
{
	if (!head)
		return;
	if (quote)
		fprintout(format("%s='%s'\n", head->var, head->val));
	else
		fprintout(format("%s=%s\n", head->var, head->val));
	print_list(head->next, quote);
}


/**
 * free_list - frees all nodes and their contents.
 *
 * @head: the head of the linked list
 *
 * Return: nothing
 */
void free_list(node *head)
{
	if (!head)
		return;
	free_list(head->next);
	if (head->var)
		free(head->var);
	if (head->val)
		free(head->val);
	free(head);
}


/**
 * add_node - adds a node at the beginning of a linked list
 *
 * @head: a pointer to a pointer to the head of the list 🙃
 * @var: the name of the node
 * @val: the value associated with the node
 *
 * Return: new node
 */
node *add_node(node **head, const char *var, const char *val)
{
	node *new_node;

	new_node = malloc(sizeof(new_node));
	if (!new_node)
		return (NULL);
	new_node->var = _strdup(var);
	new_node->val = _strdup(val);
	if (!(new_node->var && new_node->val))
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}


/**
 * add_node_end - adds a node to the end of a linked list
 *
 * @head: a pointer to a pointer to the head of the list 🙃
 * @var: the name of the node
 * @val: the value associated with the node
 *
 * Return: pointer to new node
 */
node *add_node_end(node **head, const char *var, const char *val)
{
	node *new_node, *tail;

	new_node = malloc(sizeof(node));
	if (!new_node)
		return (NULL);
	new_node->var = _strdup(var);
	new_node->val = _strdup(val);
	if (!(new_node->var && new_node->val))
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		tail = get_tail(*head);
		tail->next = new_node;
	}
	return (new_node);
}


/**
 * get_node - finds a node using it's name
 *
 * @head: the head of the list
 * @var: the name of the node
 *
 * Return: the first node with that name.
 *		If no node is found with that name, NULL is returned.
 */
node *get_node(node *head, const char *var)
{
	if (!head)
		return (NULL);
	if (!_strcmp(head->var, var))
		return (head);
	return (get_node(head->next, var));
}

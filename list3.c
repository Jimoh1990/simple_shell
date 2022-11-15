#include "shell.h"

/**
 * set_node - sets a new value on a node
 * if the node doesn't exist, is it created and added to the list.
 *
 * @head: a pointer to the head of the list
 * @var: the name of the node
 * @val: the value to assign to the node
 *
 * Return: the target.
 * NULL is returned when the node could not be created.
 */
node *set_node(node **head, const char *var, const char *val)
{
	node *target;

	if (!head)
		return (NULL);

	target = get_node(*head, var);

	if (!target)
		return (add_node_end(head, var, val));
	if (target->val)
		free(target->val);
	target->val = strdup(val);
	return (target);

}

/**
 * set_default - creates a new node only if it doesn't exist
 * if the node exists, is it returned.
 *
 * @head: a pointer to the head of the list
 * @var: the name of the node
 * @val: the value to assign to the node
 *
 * Return: the target.
 * NULL is returned when the node could not be created.
 */
node *set_default(node **head, const char *var, const char *val)
{
	node *target;

	if (!head)
		return (NULL);

	target = get_node(*head, var);

	if (!target)
		return (add_node_end(head, var, val));
	return (target);
}

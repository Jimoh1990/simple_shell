#include "shell.h"

/**
 * listlen - returns the length of a list
 *
 * @head: the head of a list
 *
 * Return: number of nodes in a list.
 */
size_t listlen(node *head)
{
	if (!head)
		return (0);
	return (1 + listlen(head->next));
}


/**
 * get_tail - gets the last node in a list
 *
 * @head: the head of the list
 *
 * Return: the last node.
 *		NULL is returned if the list is empty.
 */
node *get_tail(node *head)
{
	if (!head)
		return (NULL);
	if (!head->next)
		return (head);
	return (get_tail(head->next));
}


/**
 * delete_node - deletes a node from a list
 *
 * @head: a pointer to the head of the list
 * @var: the name of the node to delete
 *
 * Return: true if the node was deleted.
 *		false is returned if the node was not found
 */
bool delete_node(node **head, const char *var)
{
	node *temp, *target;

	if (!(head && *head))
		return (false);

	temp = NULL;
	target = *head;

	while (target)
	{
		if (!_strcmp(target->var, var))
			break;
		temp = target;
		target = target->next;
	}
	if (!target)
		return (false);
	if (!temp)
		*head = target->next;
	else
		temp->next = target->next;
	if (target->var)
		free(target->var);
	if (target->val)
		free(target->val);
	free(target);
	return (true);
}


/**
 * from_strarr - this function creates a linked list from an array of strings
 *
 * @array: an array of strings
 *
 * Return: the head of a linked list. NULL is returned if the array is empty
 *
 * NOTE: the array should be null-terminated.
 * The strings should be in this format: VAR=VAL
 */
node *from_strarr(char **array)
{
	node *head;
	char *str, *var, *val, **arr;
	int i;

	if (!array || !array[0] || !array[0][0])
		return (NULL);

	head = NULL;
	for (i = 0; array[i]; i++)
	{
		str = _strdup(array[i]);
		arr = split(str, "=", 1, false);
		var = arr[0];
		val = arr[1];
		add_node_end(&head, var, val);
		free(str);
		free(arr);
	}
	return (head);
}


/**
 * to_strarr - this function creates an array of strings from a linked list
 *
 * @head: the head of a linked list
 *
 * Return: a null-terminated array of strings.
 *		NULL is returned if the list is empty.
 *
 * NOTE: the string in the array are in this format: VAR=VAL
 */
char **to_strarr(node *head)
{
	char **array, *buffer;
	node *n;
	size_t arr_size, buf_size;
	int arr_ind, buf_ind, i;

	if (!head)
		return (NULL);

	n = head;
	arr_size = 1 + listlen(head);
	array = malloc(NPTRS(arr_size));
	arr_ind = 0;

	while (n)
	{
		buf_size = 2 + _strlen(n->var) + _strlen(n->val);
		buffer = malloc(NCHARS(buf_size));
		buf_ind = 0;

		for (i = 0; n->var[i]; i++)
			buffer[buf_ind++] = n->var[i];

		buffer[buf_ind++] = '=';

		for (i = 0; n->val[i]; i++)
			buffer[buf_ind++] = n->val[i];

		buffer[buf_ind] = '\0';
		array[arr_ind++] = buffer;
		n = n->next;
	}
	array[arr_ind] = NULL;
	return (array);
}

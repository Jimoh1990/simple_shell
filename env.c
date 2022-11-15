#include "shell.h"
/**
 * _env - prints out all env variables
 *
 * @env: the environment
 * Return: 0 if success
 */
int _env(node *env)
{
	print_list(env);
	return (0);

}

/**
 * _setenv - sets a new environmental variable
 *
 * @name: the name of the variable
 * @value: its value
 * @env: the environment
 * Return: 0
 */
int _setenv(char *name, char *value, node **env)
{
	set_node(env, name, value);
	return (0);
}
/**
 * _unsetenv - deletes a variable
 *
 * @name: the name of the variable
 * @env: the environment
 * Return: 0 if successful
 */
int _unsetenv(char *name, node **env)
{
	delete_node(env, name);
	return (0);
}

/*
 * ________________________________________________________________________________
 * |  File: builtins.c
 * |  Project: source
 * |  File Created: Saturday, 11th January 2025 08:26 am
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#include "../includes/program.h"

int check_for_builtins(char **line, t_program *c)
{
	if (strcmp(line[0], "exit") == 0)
		cleanup(c);
	if (strcmp(line[0], "cd") == 0)
	{
		change_directory_builtin(line, c->env);
		return (1);
	}
	if (strcmp(line[0], "echo") == 0)
		return 0;
	if (strcmp(line[0], "pwd") == 0)
		return 0;
	if (strcmp(line[0], "export") == 0)
	{
		export_builtin(line, c);
		return 1;
	}
	if (strcmp(line[0], "unset") == 0)
	{
		unset_builtin(line, c);
		return 1;
	}
	if (strcmp(line[0], "history") == 0)
		return 0;
	if (strcmp(line[0], "env") == 0)
	{
		print_list_2d(c->env);
		return 1;
	}
		
	return 0;
}

void unset_builtin(char **line, t_program *c)
{
	if (line[1])
		c->env = unset_env_yosh(line[1], c->env);
	else
		return ;
}

void export_builtin(char **line, t_program *c)
{
	if (line[1])
		c->env = set_env_yosh(line[1], c->env);
	else
		return ;
}

void change_directory_builtin(char **line, char **env)
{
	char *token_cat	= concatenate_tokens(&line[1]);
	if(strcmp(token_cat, "~") == 0)
	{
		if (chdir(get_env_yosh("HOME", env)))
			save_to_error_txt("$HOME variable unset");
		return ;	
	}
	if(chdir(token_cat))
	{
		save_to_error_txt("directory does not exist");
	}

}
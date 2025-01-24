/*
 * ________________________________________________________________________________
 * |  File: env.c
 * |  Project: source
 * |  File Created: Friday, 13th December 2024 05:51 am
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#include "../includes/program.h"

char *get_programs_path(char *program, char **env)
{
	if (strncmp(program, "./", 2) == 0)
		return program;
	char *paths = get_env_yosh("PATH", env);
	char **splitpaths = split(paths, ':');
	safe_free(paths);
	int i;

	i = 0;
	while (splitpaths[i])
	{
		char *filepath = strjoin_e(3, splitpaths[i], "/", program);
		if (access(filepath, F_OK) == 0)
		{
			safe_free(splitpaths);
			return filepath;
		}
		safe_free(filepath);
		i += 1;
	}
	safe_free(splitpaths);
	return NULL;
}

char *get_env_yosh(char *var, char **env)
{
	if (strcmp(var, "") == 0)
		return "";

	char *variable;
	int i;
	int namelen;

	namelen = strlen(var);
	i = 0;
	while (env[i])
	{
		if ((strncmp(var, env[i], namelen) == 0))
		{
			if (env[i][namelen] == '=')
			{
				int varlen = strlen(env[i]) - (namelen + 1);
				variable = substr(env[i], namelen + 1, varlen);
				return variable;				
			}
		}
		i += 1;
	}
	return "";
}

static int is_update_env(char *var, char **env)
{
	char *key = strdup(var);
	if (!key) return -1;

	char *equals_sign = strchr(key, '=');
	if (equals_sign) *equals_sign = '\0';

	int i = 0;
	while (env[i])
	{
		if (strncmp(key, env[i], strlen(key)) == 0 && env[i][strlen(key)] == '=')
		{
			free(key);
			return i;
		}
		i++;
	}

	free(key);
	return -1;
}

char **set_env_yosh(char *var, char **env)
{
	if (!env_naming_check(var))
		return env;

	int index = is_update_env(var, env);
	if (index >= 0)
	{
	    free(env[index]);
	    env[index] = strdup(var);
	    return env;
	}	
	int len = lstlen(env);
	char **newenv = malloc(sizeof(char *) * (len + 2));
	
	if (!newenv) return env;	
	
	tabcpy(newenv, env);
	newenv[len] = strdup(var);
	newenv[len + 1] = NULL;	
	
	free(env);	
	return newenv;
}

int env_naming_check(char *var)
{
	if(var[0] == '=')
	{
		save_to_error_txt("environment variable being set must have a name");
		return 0;
	} 
	else if (!isupper(var[0]) && var[0] != '_')
	{
		save_to_error_txt("environment variables must not start with a lowercase letter or number or special character");
		return 0;
	}
		
	int i;

	i = 1;
	while (var[i] != '=' && var[i] != '\0')
	{
		if (!isalpha(var[i]) && !isdigit(var[i]) && var[i] != '_')
		{
			save_to_error_txt("characters beyond the first must be alphabetic or numeric or use underscores");
			return 0;
		}
		i += 1;
	}

	if(var[i] != '=')
	{
		save_to_error_txt("environment variable must contain an '=' character");
		return 0;
	}
	return 1;
}

char **unset_env_yosh(char *var, char **env)
{
	if (strcmp(var, "USER") == 0)
		return env;
	int index = is_update_env(var, env);
	if (index == -1)
	{
		printf("Environment Variable Does Not Exist");
		return env;
	}
	if (env[index + 1] == NULL)
	{
		env[index] = NULL;
		return env;
	}

	char **newenv;
	newenv = malloc(sizeof(char *) * lstlen(env));
	if (!newenv)
		return NULL;
	int i = 0;
	int q = 0;
	while (env[q])
	{
		if (index == i)
			q++;
		newenv[i] = strdup(env[q]);
		i += 1;
		q += 1;
	}
	newenv[i] = NULL;
	safe_free_2d_char(env);
	return (newenv);
}
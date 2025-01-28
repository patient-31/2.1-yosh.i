/*
 * ________________________________________________________________________________
 * |  File: init.c
 * |  Project: source
 * |  File Created: Thursday, 12th December 2024 05:05 pm
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#include "../includes/program.h"

void init(t_program *c, char **envp)
{

	c->line_read = NULL;
	c->prompt = NULL;
	c->exit_status = 0;
	c->env = tabdup(envp);
	c->home = get_env_yosh("HOME", c->env);
	c->yosh_history = strjoin_e(2, c->home, "/.yosh_history");

	c->black = strdup("\001\033[0;30m\002");
	c->red = strdup("\001\033[0;31m\002");
	c->green = strdup("\001\033[0;32m\002");
	c->yellow = strdup("\001\033[0;33m\002");
	c->blue = strdup("\001\033[0;34m\002");
	c->magenta = strdup("\001\033[0;35m\002");
	c->cyan = strdup("\001\033[0;36m\002");
	c->white = strdup("\001\033[0;37m\002");
	
	c->bold_black = strdup("\001\033[1;30m\002");
	c->bold_red = strdup("\001\033[1;31m\002");
	c->bold_green = strdup("\001\033[1;32m\002");
	c->bold_yellow = strdup("\001\033[1;33m\002");
	c->bold_blue = strdup("\001\033[1;34m\002");
	c->bold_magenta = strdup("\001\033[1;35m\002");
	c->bold_cyan = strdup("\001\033[1;36m\002");
	c->bold_white = strdup("\001\033[1;37m\002");



}
/*
 * ________________________________________________________________________________
 * |  File: setup.c
 * |  Project: source
 * |  File Created: Thursday, 12th December 2024 04:45 pm
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#include "../includes/program.h"

void set_prompt(t_program *c)
{
	safe_free(c->prompt);

	c->user = get_env_yosh("USER", c->env);
	if (!c->user)
		c->user = strdup("Undefined");
	getcwd(c->cwd, 1024);
	c->base_name = basename(c->cwd);	
	gethostname(c->hostname, 256);

	c->exit_status_str = itoa(c->exit_status);


	c->prompt = strjoin_e(16, 
							c->magenta, 
							c->user, 
							c->white, 
							"@", 
							c->magenta, 
							c->hostname, 
							c->bold_red, 
							" :: ", 
							c->bold_blue, 
							c->base_name, 
							c->cyan, 
							" [", 
							c->bold_red, 
							c->exit_status_str,
							c->cyan, 
							"] >");

	safe_free(c->user);
	safe_free(c->exit_status_str);

}

int command_input(t_program *c)
{
	set_prompt(c);
	safe_free(c->line_read);

	c->line_read = readline(c->prompt);
	if (c->line_read)
	{
		if(is_whitespace(c->line_read))
			return (0);
		add_history(c->line_read);
		return (1);
	}
	else if (!c->line_read)
	{
		cleanup(c);
		exit(0);
	}
		
	return (0);

}
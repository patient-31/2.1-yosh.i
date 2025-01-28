/*
 * ________________________________________________________________________________
 * |  File: main.c
 * |  Project: source
 * |  File Created: Tuesday, 10th December 2024 03:09 pm
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#include "../includes/program.h"
void	entry_message(void)
{
    printf("\n");
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║🐚                                          🐚║\n");
    printf("║    Welcome to yosh.i 2.1, Your Interactive   ║\n");
    printf("║              Shell Experience                ║\n");
    printf("║🐚                                          🐚║\n");
    printf("╚══════════════════════════════════════════════╝\n");
    sleep(1);
}



int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (strlen(argv[0]));
	t_program *c = NULL;
	c = exit_malloc(sizeof(t_program), "Critical Program Struct Allocation Failed", c);
	if (!c)
		exit(-1);


	init(c, envp);

	using_history();

	open(c->yosh_history, 0600);
	load_history(c->yosh_history);
	entry_message();

	while (1)
	{

		if (!command_input(c))
			continue ;
		save_history(c->yosh_history);
		char **expanded = expand_env_and_split_w_quotes(c->line_read, c->env);
		if (expanded[0] == NULL)
		{
			printf("Undefined Input\n");
			continue ;
		}
		run_cmd(expanded, c);
		safe_free_2d_char(expanded);
		
	}
	cleanup(c);
}



void	cleanup(t_program *c)
{
	printf("\nexiting\n");
	save_history(c->yosh_history);
	safe_free_2d_char(c->env);
	safe_free(c->line_read);
	safe_free(c->prompt);
	safe_free(c->yosh_history);
	safe_free(c->home);


	safe_free(c->black);
	safe_free(c->red);
	safe_free(c->green);
	safe_free(c->yellow);
	safe_free(c->blue);
	safe_free(c->magenta);
	safe_free(c->cyan);
	safe_free(c->white);

	safe_free(c->bold_black);
	safe_free(c->bold_red);
	safe_free(c->bold_green);
	safe_free(c->bold_yellow);
	safe_free(c->bold_blue);
	safe_free(c->bold_magenta);
	safe_free(c->bold_cyan);
	safe_free(c->bold_white);



	safe_free(c);
	exit(0);
}
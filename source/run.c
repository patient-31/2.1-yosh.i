/*
 * ________________________________________________________________________________
 * |  File: run.c
 * |  Project: source
 * |  File Created: Friday, 10th January 2025 04:41 pm
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#include "../includes/program.h"
#include <sys/wait.h> // included here for linux compatibility


void run_cmd(char **expanded, t_program *c)
{
	if (check_for_builtins(expanded, c))
		return ;
	
	// if (check_for_redirections(expanded, c))
	// 	run_cmd_w_redirections(expanded, c);
	
	run_simple_cmd(expanded, c);	
}


void	run_simple_cmd(char **expanded, t_program *c)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		save_to_error_txt("Could not create child process.");
	else if (pid == 0)
	{
		if (execve(get_programs_path(expanded[0], c->env), expanded, c->env) == -1)
		{
			save_to_error_txt(strjoin_e(2, "yosh.i: command not found: ", expanded[0]));
			exit(errno);
		}
	}
	waitpid(pid, &c->exit_status, WCONTINUED);
	if (WIFEXITED(c->exit_status))
		printf("\nChild process exited normally.\n");
}



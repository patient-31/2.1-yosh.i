/*
 * ________________________________________________________________________________
 * |  File: program.h
 * |  Project: includes
 * |  File Created: Tuesday, 10th December 2024 03:20 pm
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#ifndef PROGRAM_H
# define PROGRAM_H


# include "../libdanc/includes/libdanc.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <libgen.h>
# include <unistd.h>

# include "program_func.h"

typedef struct s_program 
{

	char 	*home;
	int		exit_status;
	char	*exit_status_str;
	char	**env;
	char	*yosh_history;
	char	*yosh_irc;
	char	*prompt;
	char	*line_read;
	char 	hostname[256];
	char 	cwd[1024];
	char 	*user;
	char 	*base_name;


	char 	*black;
    char 	*red;
    char 	*green;
    char 	*yellow;
    char 	*blue;
    char 	*magenta;
    char 	*cyan;
    char 	*white;
	
    char 	*bold_black;
    char 	*bold_red;
    char 	*bold_green;
    char 	*bold_yellow;
    char 	*bold_blue;
    char 	*bold_magenta;
    char 	*bold_cyan;
    char 	*bold_white;


} t_program;

#endif
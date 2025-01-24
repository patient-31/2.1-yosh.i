/*
 * ________________________________________________________________________________
 * |  File: history.c
 * |  Project: source
 * |  File Created: Thursday, 12th December 2024 08:27 am
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#include "../includes/program.h"

void	load_history(char *filename)
{
	if (read_history(filename) != 0)
		save_to_error_txt("Unable to load history file\n");
}

void	save_history(char *filename)
{
	if (write_history(filename) != 0)
		save_to_error_txt("Unable to save history file\n");
}
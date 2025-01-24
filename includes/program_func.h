/*
 * ________________________________________________________________________________
 * |  File: program_func.h
 * |  Project: includes
 * |  File Created: Thursday, 12th December 2024 04:42 pm
 * |  Author: Daniel Haddington [haddingtondaniel5@icloud.com]
 */

#ifndef PROGRAM_FUNC_H
# define PROGRAM_FUNC_H

# include "program.h"

/** BUILTINS.C */
int		check_for_builtins(char **line, t_program *c);
void 	change_directory(char **line, char **env);
void 	export_to_env(char **line, t_program *c);
void 	unset_to_env(char **line, t_program *c);

/** env.c */

char	*get_programs_path(char *program, char **env);
char	*get_env_yosh(char *var, char **env);
char 	**set_env_yosh(char *var, char **env);
char 	**unset_env_yosh(char *var, char **env);
int		env_naming_check(char *var);

/** gpt.c */

/** */
char **expand_env_and_split_w_quotes(const char *input, char **env);

/** history.c */

/** */
void	load_history(char *filename);
/** */
void	save_history(char *filename);



/** init.c */

void _init(t_program *c, char **envp);



/** main.c */

void	entry_message(void);
void	cleanup(t_program *c);

/** run.c */

/** */
void run_cmd(char **expanded, t_program *c);
void	run_simple_cmd(char **expanded, t_program *c);


/** setup.c */

/** */
void set_prompt(t_program *c);
/** */
int command_input(t_program *c);




#endif
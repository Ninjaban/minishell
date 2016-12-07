/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:44:38 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/07 10:56:43 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
**	Macros
*/

# define NAME "Minishell"
# define PROMPT "\033[34;1;4m$: commande nº!#\033[0m - (\033[31m!W\033[0m) => "
# define HISTORY_SIZE 1000
# define FALSE 0
# define TRUE 1
# define EXIT "exit"

/*
**	Includes
*/

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

/*
**	Structures
*/

typedef struct	s_cmd
{
	char			*name;
	char			**argv;
	pid_t			child;
}				t_cmd;

typedef struct	s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
}				t_alias;

typedef struct	s_sys
{
	t_alias			*alias;
	t_cmd			**cmds;
	char			**env;
	char			**history;
}				t_sys;

/*
**	Functions
*/

void			ft_error(char *error);
void			ft_free_tab(char **t);
void			ft_free_cmds(t_cmd **cmds);
void			ft_shell(t_sys *sys, int exit);
void			ft_affprompt(size_t nbcmd, char **env);
void			ft_prompt_path(char **t, char b);
void			ft_init_changedir(char **pwd, char **t, char ***env);
void			*ft_gestion_error(t_cmd **cmds);
void			*ft_exec(t_sys **sys);
int				ft_access_dir(char *path);
int				ft_changedir(char *name, char *pwd, char *dir, char ***env);
int				ft_history_maj(char ***history, char *line, char **env);
int				ft_alias(t_cmd *cmd, t_alias **alias);
char			*ft_access(char *name, char **env);
char			*ft_cvar(char *name, char *value);
char			*ft_joinpath(char *src, char *str);
char			*ft_delchar(char *str, size_t n);
char			**ft_history_init(char **env);
char			**ft_getpath(char **env);
t_cmd			**ft_parsing(char *str);

/*
**	Builtins
*/

void			ft_echo(char **argv);
void			ft_env(char **env);
void			ft_unsetenv(char ***env, char *str);
void			ft_setenv(char *str, char ***env, int b);
void			ft_chdir(char ***env, char *str);

/*
**	Termcaps
*/

int				fputchar(int c);
int				ft_goto(char *cmd, int col, int line);
int				ft_termcaps_end(void);
int				ft_termcaps_init(void);

#endif

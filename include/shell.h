/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:44:38 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/28 10:55:31 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
**	Macros
*/

# define NAME "Minishell"
# define PROMPT "\033[34;1;4m$: commande nº!#\033[0m - (\033[31m!W\033[0m)\n=> "
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
	char		*name;
	char		**argv;
	pid_t		child;
}				t_cmd;

/*
**	Functions
*/

void			ft_error(char *error);
void			ft_free_tab(char **tab);
void			ft_free_cmds(t_cmd **cmds);
void			ft_shell(char **env, int exit);
void			ft_affprompt(size_t nbcmd, char **env);
void			ft_prompt_path(char **tab, char bool);
void			ft_init_changedir(char **pwd, char **tab, char ***env);
void			*ft_gestion_error(t_cmd **cmds);
void			*ft_exec(t_cmd **cmds, char ***env);
int				ft_access_dir(char *path);
int				ft_changedir(char *name, char *pwd, char *dir, char ***env);
int				ft_history_maj(char ***history, char *line, char **env);
char			*ft_access(char *name, char **env);
char			*ft_cvar(char *name, char *value);
char			*ft_joinpath(char *src, char *str);
char			**ft_history_init(char **env);
char			**ft_getpath(char **env);
t_cmd			**ft_parsing(char *str);

/*
**	Builtins
*/

void			ft_echo(char **argv);
void			ft_env(char **env);
void			ft_unsetenv(char ***env, char *str);
void			ft_setenv(char *str, char ***env, int bool);
void			ft_chdir(char ***env, char *str);

#endif

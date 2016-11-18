/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:44:38 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/18 15:59:02 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define NAME "Minishell"
# define PROMPT "$> "
# define FALSE 0
# define TRUE 1
# define EXIT "exit"

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct	s_cmd
{
	char		*name;
	char		**argv;
	pid_t		child;
}				t_cmd;

/*
**	Functions
*/

void		ft_error(char *error);
void		ft_free_tab(char **tab);
void		ft_free_cmds(t_cmd **cmds);
void		*ft_gestion_error(t_cmd **cmds);
void		*ft_exec(t_cmd **cmds, char ***env);
void		ft_shell(char **env, int exit);
int			ft_access_dir(char *path);
char		*ft_access(char *name, char **env);
char		**ft_getpath(char **env);
t_cmd		**ft_parsing(char *str);

/*
**	Builtins
*/

void		ft_echo(char **argv);
void		ft_env(char **env);
void		ft_unsetenv(char ***env, char *str);
void		ft_setenv(char *str, char ***env);
void		ft_chdir(char ***env, char *str, size_t i);

#endif

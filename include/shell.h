/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:44:38 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 12:06:55 by jcarra           ###   ########.fr       */
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
void		ft_free_cmds(t_cmd **cmds);
void		*ft_gestion_error(t_cmd **cmds);
void		*ft_exec(t_cmd **cmds, char **env);
int			ft_shell(char **env, int exit);
t_cmd		**ft_parsing(char *str);

#endif

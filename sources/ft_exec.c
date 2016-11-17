/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 21:39:38 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static void	ft_exec_child(t_cmd *cmds, char **env)
{
	char	*cmd;

	if ((cmd = ft_access(cmds->name, env)) != NULL)
	{
		if (ft_strcmp(cmds->name, "echo") == 0)
			ft_echo(cmds->argv);
		if (execve(cmd, cmds->argv, env) == -1)
			ft_error(ERROR_EXEC);
		free(cmd);
	}
	exit(0);
}

void		*ft_exec(t_cmd **cmds, char **env)
{
	size_t	n;
	int		status;

	n = 0;
	while (cmds[n])
	{
		if (cmds[n]->name)
		{
			if (ft_strcmp(cmds[n]->name, "exit") == 0)
				return (EXIT);
			if ((cmds[n]->child = fork()) == -1)
				return (ERROR_FORK);
			if (cmds[n]->child == 0)
				ft_exec_child(cmds[n], env);
			else
				wait(&status);
		}
		n = n + 1;
	}
	if (env)
		return (NULL);
	return (NULL);
}

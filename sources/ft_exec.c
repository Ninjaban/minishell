/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 14:06:33 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

void		*ft_exec(t_cmd **cmds, char **env)
{
	size_t	n;
	int		status;
	int		ret;

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
			{
				ft_putendl("Child start");
				ret = execve(cmds[n]->name, cmds[n]->argv, env);
				perror(NAME);
				ft_putendl("\nChild end");
				exit(0);
			}
			else
			{
				ft_putendl("Wait child.");
				wait(&status);
				ft_putendl("End child.");
			}
		}
		n = n + 1;
	}
	if (env)
		return (NULL);
	return (NULL);
}

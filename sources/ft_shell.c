/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 11:40:23 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

int			ft_shell(char **env, int exit)
{
	t_cmd	**cmds;
	char	*str;
	char	*tmp;

	while (exit == FALSE)
	{
		ft_putstr(PROMPT);
		cmds = NULL;
		if (get_next_line(0, &str) == -1)
			ft_error(ERROR_READ);
		else if ((cmds = ft_parsing(str)) == NULL)
			ft_error(ERROR_ALLOC);
		else if ((tmp = ft_gestion_error(cmds)) != NULL)
			ft_error(tmp);
		else if ((tmp = ft_exec(cmds, env)) != NULL)
		{
			if (tmp != EXIT)
				ft_error(tmp);
			else
				exit = TRUE;
		}
		if (cmds)
			ft_free_cmds(cmds);
	}
	return (0);
}

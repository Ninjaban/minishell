/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/18 19:05:11 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static void	ft_free(t_cmd **cmds, char *str)
{
	if (str)
		free(str);
	if (cmds)
		ft_free_cmds(cmds);
}

void		ft_shell(char **env, int exit)
{
	t_cmd	**cmds;
	char	*str;
	char	*tmp;

	while (exit == FALSE)
	{
		ft_putstr(PROMPT);
		cmds = NULL;
		str = NULL;
		if (get_next_line(0, &str) == -1)
			ft_error(ERROR_READ);
		else if ((cmds = ft_parsing(str)) == NULL)
			ft_error(ERROR_ALLOC);
		else if ((tmp = ft_gestion_error(cmds)) != NULL)
			ft_error(tmp);
		else if ((tmp = ft_exec(cmds, &env)) != NULL)
		{
			if (ft_strcmp(tmp, EXIT) != 0)
				ft_error(tmp);
			else
				exit = TRUE;
		}
		ft_free(cmds, str);
	}
	ft_free_tab(env);
}

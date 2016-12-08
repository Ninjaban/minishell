/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/08 15:46:32 by jcarra           ###   ########.fr       */
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

static int	ft_launcher(t_sys **sys, char **str)
{
	static size_t	n = 0;
	char			*tmp;

	ft_affprompt(++n, (*sys)->env);
	(*sys)->cmds = NULL;
	*str = NULL;
	if (get_next_line(0, &(*str)) == -1)
		ft_error(ERROR_READ);
	else if ((ft_history_maj(&((*sys)->history), *str, (*sys)->env)) == FALSE)
		ft_error(ERROR_ALLOC);
	else if (((*sys)->cmds = ft_parsing(*str, *sys)) == NULL)
		ft_error(ERROR_ALLOC);
	else if ((tmp = ft_gestion_error((*sys)->cmds)) != NULL)
		ft_error(tmp);
	else
		return (TRUE);
	return (FALSE);
}

static int	ft_shrc_init(t_sys **sys, char *str, int fd)
{
	char	*tmp;

	(*sys)->alias = NULL;
	if ((fd = open(ft_strjoin(ft_getenv((*sys)->env, "HOME"), "/.42shrc"),
					O_RDONLY)) == -1)
		return (FALSE);
	while (get_next_line(fd, &str) == 1)
	{
		if ((ft_history_maj(&((*sys)->history), str, (*sys)->env)) == FALSE)
			ft_error(ERROR_ALLOC);
		else if (((*sys)->cmds = ft_parsing(str, *sys)) == NULL)
			ft_error(ERROR_ALLOC);
		else if ((tmp = ft_gestion_error((*sys)->cmds)) != NULL)
			ft_error(tmp);
		else if ((*sys)->cmds[0])
		{
			if ((ft_strcmp((*sys)->cmds[0]->name, "setenv") == 0) ||
				(ft_strcmp((*sys)->cmds[0]->name, "export") == 0))
				ft_setenv((*sys)->cmds[0]->argv[1], &((*sys)->env), FALSE);
			else if (ft_strcmp((*sys)->cmds[0]->name, "alias") == 0)
				ft_alias((*sys)->cmds[0], &((*sys)->alias));
		}
		ft_free((*sys)->cmds, str);
	}
	return (TRUE);
}

void		ft_shell(t_sys *sys, int exit)
{
	char	*str;
	char	*tmp;

	if ((sys->history = ft_history_init(sys->env)) == NULL)
	{
		ft_error(ERROR_READ);
		return ;
	}
	if (ft_shrc_init(&sys, NULL, 0) == FALSE)
		ft_error(ERROR_RC);
	while (exit == FALSE)
	{
		if (ft_launcher(&sys, &str) == TRUE)
			if ((tmp = ft_exec(&sys)) != NULL)
			{
				if (ft_strcmp(tmp, EXIT) != 0)
					ft_error(tmp);
				else
					exit = TRUE;
			}
		ft_free(sys->cmds, str);
	}
	ft_alias_remove(&(sys->alias));
	ft_free_tab(sys->history);
	ft_free_tab(sys->env);
}

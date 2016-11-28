/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/28 10:53:31 by jcarra           ###   ########.fr       */
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

static int	ft_launcher(char ***env, t_cmd ***cmds, char **str, char ***history)
{
	static size_t	n = 0;
	char			*tmp;

	ft_affprompt(++n, *env);
	*cmds = NULL;
	*str = NULL;
	if (get_next_line(0, &(*str)) == -1)
		ft_error(ERROR_READ);
	else if ((ft_history_maj(&(*history), *str, *env)) == FALSE)
		ft_error(ERROR_ALLOC);
	else if ((*cmds = ft_parsing(*str)) == NULL)
		ft_error(ERROR_ALLOC);
	else if ((tmp = ft_gestion_error(*cmds)) != NULL)
		ft_error(tmp);
	else
		return (TRUE);
	return (FALSE);
}

void		ft_shell(char **env, int exit)
{
	t_cmd	**cmds;
	char	**history;
	char	*str;
	char	*tmp;

	if ((history = ft_history_init(env)) == NULL)
	{
		ft_error(ERROR_READ);
		return ;
	}
	while (exit == FALSE)
	{
		if (ft_launcher(&env, &cmds, &str, &history) == TRUE)
			if ((tmp = ft_exec(cmds, &env)) != NULL)
			{
				if (ft_strcmp(tmp, EXIT) != 0)
					ft_error(tmp);
				else
					exit = TRUE;
			}
		ft_free(cmds, str);
	}
	ft_free_tab(history);
	ft_free_tab(env);
}

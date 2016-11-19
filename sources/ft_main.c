/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 09:29:30 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/19 13:09:43 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char	**ft_tabcpy(char **tab)
{
	char	**cpy;
	int		n;

	n = 0;
	if (!tab)
		return (NULL);
	if ((cpy = malloc(sizeof(char *) * (ft_tablen(tab) + 1))) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (NULL);
	}
	while (tab[n])
		cpy[n++] = NULL;
	cpy[n] = NULL;
	n = -1;
	while (tab[++n])
		if ((cpy[n] = ft_strdup(tab[n])) == NULL)
		{
			ft_error(ERROR_ALLOC);
			ft_free_tab(cpy);
			return (NULL);
		}
	return (cpy);
}

int			main(int ac, char **av, char **env)
{
	char	**cpy;

	if ((cpy = ft_tabcpy(env)) == NULL)
		return (1);
	ft_shell(cpy, FALSE);
	if (ac && av && env)
		return (0);
	return (0);
}

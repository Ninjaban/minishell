/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:09:52 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/07 10:31:52 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static t_alias	*ft_alias_new(char *key, char *value)
{
	t_alias	*new;

	if ((new = malloc(sizeof(t_alias))) == NULL)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = (value != NULL) ? ft_strdup(value) : NULL;
	return (new);
}

static int		ft_alias_init(t_cmd *cmd, t_alias **alias)
{
	char	**tab;

	if ((tab = ft_strsplit(cmd->argv[1], '=')) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	if (!tab[0])
	{
		free(tab);
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	if (((*alias) = ft_alias_new(tab[0], tab[1])) == NULL)
	{
		ft_free_tab(tab);
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	ft_free_tab(tab);
	return (TRUE);
}

static int		ft_alias_add(t_cmd *cmd, t_alias **alias)
{
	t_alias	*tmp;
	char	**tab;

	if ((tab = ft_strsplit(cmd->argv[1], '=')) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	if (!tab[0])
	{
		free(tab);
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	tmp = *alias;
	while (tmp->next)
		tmp = tmp->next;
	if ((tmp->next = ft_alias_new(tab[0], tab[1])) == NULL)
	{
		ft_free_tab(tab);
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	ft_free_tab(tab);
	return (TRUE);
}

int				ft_alias(t_cmd *cmd, t_alias **alias)
{
	if (!alias)
		return (FALSE);
	if (!(*alias))
	{
		if (ft_alias_init(cmd, &(*alias)) == FALSE)
			return (FALSE);
	}
	else
		if (ft_alias_add(cmd, &(*alias)) == FALSE)
			return (FALSE);
	return (TRUE);
}

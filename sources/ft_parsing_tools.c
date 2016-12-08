/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 10:33:28 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/08 15:24:56 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

char			*ft_strcut(char *str, size_t s, size_t e)
{
	size_t		n;
	char		*new;

	n = 0;
	if ((new = malloc(e - s + 1)) == NULL)
		return (NULL);
	while (s < e)
		new[n++] = str[s++];
	new[n] = '\0';
	return (new);
}

char			*ft_check_alias(char *str, t_alias *alias)
{
	t_alias		*tmp;
	char		*new;

	tmp = alias;
	while (tmp)
	{
		if ((ft_strncmp(str, tmp->key, ft_strlen(tmp->key) - 1) == 0) &&
			(ft_strlen(tmp->key) <= ft_strlen(str)) &&
			((str[ft_strlen(tmp->key)] == ' ') ||
			(str[ft_strlen(tmp->key)] == '\0')))
		{
			new = ft_strcut(str, ft_strlen(tmp->key), ft_strlen(str));
			str = ft_strjoin(tmp->value, new);
			free(new);
			return (str);
		}
		tmp = tmp->next;
	}
	return (str);
}

char			*ft_tild(char *str, char **env)
{
	size_t		n;
	char		**tab;
	char		*tmp;
	char		*new;

	if ((tab = ft_strsplit(str, '~')) == NULL)
		return (NULL);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	n = 0;
	new = ft_strdup(tab[0]);
	while (tab[++n])
	{
		tmp = ft_strjoin(new, ft_getenv(env, "HOME"));
		free(new);
		new = ft_strjoin(tmp, tab[n]);
		free(tmp);
	}
	ft_free_tab(tab);
	return (new);
}

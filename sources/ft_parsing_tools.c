/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 10:33:28 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/09 16:48:15 by jcarra           ###   ########.fr       */
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

void			ft_tild_file(char **str, char c, char r)
{
	size_t		n;

	n = 0;
	if (!str || !(*str))
		return ;
	while ((*str)[n])
	{
		if ((*str)[n] == c && n > 0 && ft_isalnum((*str)[n - 1]) == 1)
			(*str)[n] = r;
		n = n + 1;
	}
}

char			*ft_tild(char *str, char **env)
{
	size_t		n;
	char		**tab;
	char		*tmp;
	char		*new;

	ft_tild_file(&str, '~', '\a');
	if ((tab = ft_strsplit(str, '~')) == NULL || !tab[0])
		return (NULL);
	n = 0;
	new = ft_strdup(tab[0]);
	while (tab[++n])
	{
		tmp = ft_strjoin(new, ft_getenv(env, "HOME"));
		free(new);
		new = ft_strjoin(tmp, tab[n]);
		free(tmp);
	}
	tmp = (str[ft_strlen(str) - 1] == '~') ?
		ft_strjoin(new, ft_getenv(env, "HOME")) : ft_strdup(new);
	free(new);
	new = tmp;
	ft_free_tab(tab);
	ft_tild_file(&new, '\a', '~');
	return (new);
}

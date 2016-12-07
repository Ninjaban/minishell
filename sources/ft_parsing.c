/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/07 13:45:55 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char		**ft_tabcpy(char **tab)
{
	char		**dst;
	int			n;

	n = -1;
	if ((dst = malloc(sizeof(char *) * (ft_tablen(tab) + 1))) == NULL)
		return (NULL);
	while (tab[++n])
		dst[n] = ft_strdup(tab[n]);
	dst[n] = NULL;
	return (dst);
}

static char		*ft_parse_parenthesis(char *str, char c, char r)
{
	size_t		n;
	int			open;

	n = 0;
	open = FALSE;
	while (str[n])
	{
		if (str[n] == '\"')
		{
			if ((str = ft_delchar(str, (n > 0 && str[n - 1] == '\\')
									? n - 1 : n)) == NULL)
				return (NULL);
			open = (open == TRUE) ? FALSE : TRUE;
		}
		if (open == TRUE && str[n] == c)
			str[n] = r;
		n = n + 1;
	}
	return (str);
}

static void		ft_parenthesis_undo(char ***tab)
{
	size_t		n;
	size_t		i;

	n = 0;
	while ((*tab) && (*tab)[n])
	{
		i = 0;
		while ((*tab)[n][i])
		{
			if ((*tab)[n][i] == '\a')
				(*tab)[n][i] = ' ';
			i = i + 1;
		}
		n = n + 1;
	}
}

static t_cmd	*ft_parsecmd(char *str)
{
	t_cmd		*cmd;
	char		**tab;

	if ((str = ft_parse_parenthesis(str, ' ', '\a')) == NULL)
		return (NULL);
	if ((tab = ft_strsplit(str, ' ')) == NULL)
		return (NULL);
	if ((cmd = malloc(sizeof(t_cmd))) == NULL)
	{
		ft_free_tab(tab);
		return (NULL);
	}
	cmd->name = NULL;
	cmd->argv = NULL;
	ft_parenthesis_undo(&tab);
	if (!tab[0])
		return (cmd);
	if ((cmd->name = ft_strdup(tab[0])) == NULL)
	{
		ft_free_tab(tab);
		free(cmd);
		return (NULL);
	}
	cmd->argv = ft_tabcpy(tab);
	ft_free_tab(tab);
	return (cmd);
}

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
		if (ft_strncmp(str, tmp->key, ft_strlen(tmp->key) - 1) == 0 &&
			str[ft_strlen(tmp->key)] == ' ')
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

t_cmd			**ft_parsing(char *str, t_sys *sys)
{
	t_cmd		**cmds;
	char		**tab;
	int			n;

	n = 0;
	if (!str)
		return (NULL);
	if ((tab = ft_strsplit(str, ';')) == NULL)
		return (NULL);
	if ((cmds = malloc(sizeof(t_cmd) * ft_tablen(tab) + 1)) == NULL)
		return (NULL);
	while ((size_t)n < ft_tablen(tab) + 1)
		cmds[n++] = NULL;
	n = -1;
	while (tab[++n])
	{
		str = ft_check_alias(str, sys->alias);
		ft_putendl(str);
		if ((cmds[n] = ft_parsecmd(tab[n])) == NULL)
		{
			ft_free_cmds(cmds);
			return (NULL);
		}
	}
	ft_free_tab(tab);
	return (cmds);
}

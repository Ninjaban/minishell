/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/07 11:52:55 by jcarra           ###   ########.fr       */
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
			if ((*tab)[n][i] == '^')
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

	ft_putstr("1");
	if ((str = ft_parse_parenthesis(ft_strdup(str), ' ', '^')) == NULL)
		return (NULL);
	ft_putendl(str);
	if ((tab = ft_strsplit(str, ' ')) == NULL)
		return (NULL);
	ft_putstr("3");
	if ((cmd = malloc(sizeof(t_cmd))) == NULL)
	{
		ft_free_tab(tab);
		return (NULL);
	}
	ft_putstr("4");
	cmd->name = NULL;
	cmd->argv = NULL;
	ft_parenthesis_undo(&tab);
ft_putstr("5");
	if (!tab[0])
		return (cmd);
	if ((cmd->name = ft_strdup(tab[0])) == NULL)
	{
		ft_free_tab(tab);
		free(cmd);
		return (NULL);
	}
	ft_putstr("6");
	cmd->argv = ft_tabcpy(tab);
	ft_free_tab(tab);
	return (cmd);
}

t_cmd			**ft_parsing(char *str)
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
		if ((cmds[n] = ft_parsecmd(tab[n])) == NULL)
		{
			ft_free_cmds(cmds);
			return (NULL);
		}
	ft_free_tab(tab);
	return (cmds);
}

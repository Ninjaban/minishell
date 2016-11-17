/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 20:54:03 by jcarra           ###   ########.fr       */
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

static void		ft_parse_parenthesis(char **str, char c, char r)
{
	size_t		n;
	int			open;

	n = 0;
	open = FALSE;
	while ((*str)[n])
	{
		if ((*str)[n] == '\"')
		{
			(*str)[n++] = ' ';
			open = (open == TRUE) ? FALSE : TRUE;
		}
		if (open == TRUE && (*str)[n] == c)
			(*str)[n] = r;
		n = n + 1;
	}
}

static void		ft_parenthesis_undo(char ***tab)
{
	size_t		n;

	n = 0;
	while ((*tab)[n])
		ft_parse_parenthesis(&((*tab)[n++]), '\a', ' ');
}

static t_cmd	*ft_parsecmd(char *str)
{
	t_cmd		*cmd;
	char		**tab;

	ft_parse_parenthesis(&str, ' ', '\a');
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 12:32:09 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void			ft_free_cmds(t_cmd **cmds)
{
	int			n;

	n = 0;
	if (cmds)
	{
		while (cmds[n])
			free(cmds[n++]);
		free(cmds);
	}
}

static char		**ft_tabcpy(char **tab)
{
	char		**dst;
	int			n;

	n = -1;
	if ((dst = malloc(sizeof(char *) * ft_tablen(tab) + 1)) == NULL)
		return (NULL);
	while (tab[++n])
		dst[n] = ft_strdup(tab[n]);
	dst[n] = NULL;
	return (dst);
}

static t_cmd	*ft_parsecmd(char *str)
{
	t_cmd		*cmd;
	char		**tab;

	if ((tab = ft_strsplit(str, ' ')) == NULL)
		return (NULL);
	if ((cmd = malloc(sizeof(t_cmd))) == NULL)
	{
		free(tab);
		return (NULL);
	}
	cmd->name = NULL;
	cmd->argv = NULL;
	if (!tab[0])
		return (cmd);
	if ((cmd->name = ft_strdup(tab[0])) == NULL)
	{
		free(tab);
		free(cmd);
		return (NULL);
	}
	if (tab[1] != NULL)
		cmd->argv = ft_tabcpy(tab);
	else
		cmd->argv = NULL;
	free(tab);
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
	free(tab);
	return (cmds);
}

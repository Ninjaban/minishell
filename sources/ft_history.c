/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 08:55:19 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/07 20:06:44 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static int	ft_history_file(char **env)
{
	size_t	n;
	int		fd;
	char	**tab;
	char	*tmp;

	n = 0;
	if (!env)
		return (-1);
	while (ft_strncmp(env[n], "HOME", 3) != 0)
		n = n + 1;
	if ((tab = ft_strsplit(env[n], '=')) == NULL)
		return (-1);
	if ((tmp = ft_strjoin(tab[1], "/.42sh_history")) == NULL)
	{
		ft_free_tab(tab);
		return (-1);
	}
	fd = open(tmp, O_RDWR | O_CREAT, 0640);
	free(tmp);
	return (fd);
}

static void	ft_history_suppr_first(char ***history)
{
	size_t	n;

	n = 1;
	free(history[0]);
	while ((*history)[n])
	{
		((*history)[n - 1]) = ((*history)[n]);
		n = n + 1;
	}
	(*history)[n - 1] = NULL;
}

int			ft_history_maj(char ***history, char *line, char **env)
{
	size_t	n;
	int		fd;

	if ((fd = ft_history_file(env)) == -1)
		return (FALSE);
	n = ft_tablen(*history);
	if (n == HISTORY_SIZE)
	{
		ft_history_suppr_first(&(*history));
		n = n - 1;
	}
	(*history)[n] = ft_strdup(line);
	n = 0;
	while ((*history)[n])
		ft_putendl_fd((*history)[n++], fd);
	close(fd);
	return (TRUE);
}

char		**ft_history_init(char **env)
{
	char	**history;
	char	*line;
	size_t	n;
	int		fd;

	if (HISTORY_SIZE <= 0 || !env)
		return (NULL);
	if ((history = malloc(sizeof(char *) * HISTORY_SIZE + 1)) == NULL)
		return (NULL);
	n = 0;
	while (n < HISTORY_SIZE)
		history[n++] = NULL;
	if ((fd = ft_history_file(env)) == -1)
		return (NULL);
	n = 0;
	while (n < HISTORY_SIZE && get_next_line(fd, &line) == 0)
	{
		history[n++] = ft_strdup(line);
		free(line);
	}
	close(fd);
	return (history);
}

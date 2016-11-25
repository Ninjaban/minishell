/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 09:04:01 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/25 12:05:43 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static size_t	ft_find_path(char **env, char *str)
{
	size_t		n;

	n = 0;
	while (env[n])
		if (ft_strncmp(env[n++], str, ft_strlen(str) - 1) == 0)
			return (n - 1);
	return (n);
}

int			ft_path(char **str, char **env)
{
	size_t	n;
	char	**tab;
	char	**dir;
	char	bool;

	if (str && *str)
	{
		bool = (ft_strncmp(*str, "!w", 1) == 0) ? FALSE : -1;
		bool = (bool != FALSE && ft_strncmp(*str, "!W", 1) == 0) ? TRUE : bool;
		if (bool != -1 && env)
		{
			n = ft_find_path(env, "PWD");
			if (env[n])
			{
				tab = ft_strsplit(env[n], '=');
				if (!tab)
				{
					ft_putstr("...");
					return (FALSE);
				}
				if (bool == FALSE)
					ft_putstr(tab[1]);
				else
				{
					dir = ft_strsplit(tab[1], '/');
					n = 0;
					if (tab)
					{
						while (tab[n])
							n = n + 1;
						ft_putstr(tab[n - 1]);
						free(dir);
					}
					else
						ft_putstr("...");
				}
				free(tab);
			}
			else
				ft_putstr("...");
		}
	}
	return (FALSE);
}

int			ft_nbcmd(char **str, size_t nbcmd)
{
	if (str && *str)
	{
		if (ft_strncmp(*str, "!#", 1) == 0)
		{
			ft_putnbr(nbcmd);
			(*str)++;
			return (TRUE);
		}
	}
	return (FALSE);
}

int			ft_color(char **str)
{
	char	*tmp;
	size_t	n;

	tmp = NULL;
	if (str && *str)
		if (**str == '\033')
		{
			tmp = ft_strstr(*str, "m");
			if (*tmp)
			{
				n = tmp - *str;
				write(1, *str, n);
				while (*str != tmp - 1)
					(*str)++;
				return (TRUE);
			}
		}
	return (FALSE);
}

void		ft_affprompt(size_t nbcmd, char **env)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(PROMPT);
	tmp = str;
	if (str)
	{
		while (*str)
		{
			if (!ft_color(&str))
				if (!ft_nbcmd(&str, nbcmd))
					if (!ft_path(&str, env))
						ft_putchar(*str);
				str++;
		}
		free(tmp);
	}
}

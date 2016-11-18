/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:14:08 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/18 15:35:46 by jcarra           ###   ########.fr       */
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

static int		ft_parent(char *name, char *pwd, char ***env, size_t n)
{
	char		**tab;
	char		*str;
	char		*tmp;

	if ((tab = ft_strsplit(pwd, '/')) == NULL)
		return (-1);
	if (!tab[0])
		return (FALSE);
	str = ft_strdup("/");
	while (tab[n + 1])
	{
		if (n > 0)
		{
			tmp = ft_strjoin(str, "/");
			free(str);
			str = tmp;
		}
		tmp = ft_strjoin(str, tab[n++]);
		free(str);
		str = tmp;
	}
	ft_setenv(ft_strjoin(name, ft_strjoin("=", str)), &(*env));
	chdir(str);
	return (TRUE);
}

static int		ft_changedir(char *name, char *pwd, char *dir, char ***env)
{
	char		*tmp;
	char		*path;

	if (ft_strcmp(dir, "..") == 0)
		return (ft_parent(name, pwd, &(*env), 0));
	if ((tmp = ft_strjoin(pwd, "/")) == NULL)
		return (-1);
	if ((path = ft_strjoin(tmp, dir)) == NULL)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	if ((ft_access_dir(path)) == 1)
	{
		ft_setenv(ft_strjoin(name, ft_strjoin("=", path)), &(*env));
		chdir(path);
	}
	return (0);
}

static void		ft_home(char ***env)
{
	char		**pwd;
	char		**home;

	if ((pwd = ft_strsplit((*env)[ft_find_path((*env), "PWD")], '=')) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return ;
	}
	if ((home = ft_strsplit((*env)[ft_find_path((*env), "HOME")], '=')) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return ;
	}
	ft_setenv(ft_strjoin(pwd[0], ft_strjoin("=", home[1])), &(*env));
	chdir(home[1]);
}

void			ft_chdir(char ***env, char *str, size_t i)
{
	size_t		n;
	char		**tab;
	char		**pwd;

	if (!str || ft_strcmp(str, "~") == 0)
	{
		ft_home(&(*env));
		return ;
	}
	if ((n = ft_find_path(*env, "PWD")) == ft_tablen(*env))
	{
		ft_error(ERROR_ENV);
		return ;
	}
	if ((tab = ft_strsplit(str, '/')) == NULL)
		return ;
	if ((pwd = ft_strsplit((*env)[n], '=')) == NULL)
		return ;
	while (tab[i])
		if ((ft_changedir(pwd[0], pwd[1], tab[i++], &(*env))) == -1)
		{
			ft_error(ERROR_ALLOC);
			return ;
		}
}

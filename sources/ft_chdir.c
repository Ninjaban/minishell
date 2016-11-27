/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:14:08 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/27 11:17:03 by jcarra           ###   ########.fr       */
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

	if ((tab = ft_strsplit(pwd, '/')) == NULL)
		return (-1);
	if (!tab[0])
		return (FALSE);
	str = ft_strdup("/");
	while (tab[n + 1])
	{
		if (n > 0)
			str = ft_joinpath(str, "/");
		str = ft_joinpath(str, tab[n++]);
	}
	ft_setenv(ft_cvar(name, str), &(*env), TRUE);
	chdir(str);
	ft_free_tab(tab);
	free(str);
	return (TRUE);
}

int				ft_changedir(char *name, char *pwd, char *dir, char ***env)
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
		ft_setenv(ft_cvar(name, path), &(*env), TRUE);
		chdir(path);
	}
	free(path);
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
	ft_setenv(ft_cvar(pwd[0], home[1]), &(*env), TRUE);
	chdir(home[1]);
	ft_free_tab(pwd);
	ft_free_tab(home);
}

void			ft_chdir(char ***env, char *str)
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
	if (str[0] == '/' && ft_access_dir(str) == 1)
	{
		ft_setenv(ft_cvar("PWD", str), &(*env), TRUE);
		chdir(str);
		return ;
	}
	if ((tab = ft_strsplit(str, '/')) == NULL)
		return ;
	if ((pwd = ft_strsplit((*env)[n], '=')) == NULL)
		return ;
	ft_init_changedir(pwd, tab, &(*env));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:53:39 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/06 16:08:20 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

char		*ft_cvar(char *name, char *value)
{
	char	*tmp;
	char	*var;

	if ((tmp = ft_strjoin("=", value)) == NULL)
		return (NULL);
	if ((var = ft_strjoin(name, tmp)) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (var);
}

char		*ft_joinpath(char *src, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(src, str);
	free(src);
	return (tmp);
}

void		ft_init_changedir(char **pwd, char **tab, char ***env)
{
	size_t	n;

	n = 0;
	while (tab[n])
		if ((ft_changedir(pwd[0], pwd[1], tab[n++], &(*env))) == -1)
		{
			ft_free_tab(tab);
			ft_free_tab(pwd);
			ft_error(ERROR_ALLOC);
			return ;
		}
	ft_free_tab(tab);
	ft_free_tab(pwd);
}

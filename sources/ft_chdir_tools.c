/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:53:39 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/18 19:02:34 by jcarra           ###   ########.fr       */
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

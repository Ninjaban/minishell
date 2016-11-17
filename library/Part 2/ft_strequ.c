/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:43:42 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/03 14:56:36 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int	n;

	n = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[n] == s2[n] && s1[n] && s2[n])
		n = n + 1;
	if (s1[n] != s2[n])
		return (0);
	return (1);
}
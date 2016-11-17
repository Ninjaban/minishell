/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:02:18 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/03 14:29:31 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memcpy(void *str, const void *src, size_t n)
{
	char		*dst;
	const char	*srcs;
	size_t		i;

	dst = str;
	srcs = src;
	i = -1;
	while (++i < n)
		dst[i] = srcs[i];
	return ((void *)dst);
}

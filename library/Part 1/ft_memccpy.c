/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:04:07 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/04 15:53:19 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memccpy(void *str, const void *srcs,
									int c, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*src;
	size_t				i;

	dst = str;
	src = srcs;
	i = 0;
	if (srcs != NULL)
		while (i++ < n && *src != (unsigned char)c)
			*dst++ = *src++;
	if (*src == (unsigned char)c)
	{
		*dst++ = *src++;
		return ((void *)dst);
	}
	else
		return (NULL);
}

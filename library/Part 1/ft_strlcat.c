/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:38:04 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/07 12:50:48 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		len;

	d = dest;
	s = src;
	n = size;
	while (*d != '\0' && n-- != 0)
		d++;
	len = d - dest;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(s));
	while (*s != '\0' && n-- != 1)
		*d++ = *s++;
	while (*s != '\0')
		s++;
	*d = '\0';
	return (len + (s - src));
}

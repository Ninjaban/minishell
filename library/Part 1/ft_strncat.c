/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:30:54 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/04 12:37:56 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *dest, const char *src, size_t n)
{
	int		len;
	size_t	i;

	i = 0;
	len = ft_strlen(dest);
	while (src[i] && i < n)
		dest[len++] = src[i++];
	dest[len] = '\0';
	return (dest);
}

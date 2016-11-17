/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:09:42 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/04 17:23:27 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memmove(void *dest, const void *src, size_t n)
{
	if (n == 0)
		return (dest);
	if (dest <= src)
		dest = ft_memcpy(dest, src, n);
	else
	{
		while (--n > 0)
			((char *)dest)[n] = ((char *)src)[n];
		((char *)dest)[n] = ((char *)src)[n];
	}
	return (dest);
}

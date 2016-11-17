/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:25:52 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/04 12:30:40 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *dest, const char *src)
{
	int		len;
	int		n;

	n = 0;
	len = ft_strlen(dest);
	while (src[n])
		dest[len++] = src[n++];
	dest[len] = '\0';
	return (dest);
}

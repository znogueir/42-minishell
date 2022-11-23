/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:58:24 by znogueir          #+#    #+#             */
/*   Updated: 2022/05/16 19:45:43 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	i;
	size_t	total;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	total = ft_strlen(dst) + ft_strlen(src);
	dlen = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && i < size - dlen - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (total);
}

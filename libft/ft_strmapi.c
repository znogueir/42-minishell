/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:34:56 by znogueir          #+#    #+#             */
/*   Updated: 2022/05/10 18:00:12 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	int				slen;
	unsigned int	i;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	result = malloc(sizeof(char) * (slen + 1));
	if (!result)
		return (0);
	i = 0;
	result[slen] = '\0';
	while (s[i])
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	return (result);
}

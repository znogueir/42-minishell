/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:41:30 by znogueir          #+#    #+#             */
/*   Updated: 2022/05/17 17:51:54 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unbrlen(unsigned int un)
{
	int	len;

	len = 0;
	if (un == 0)
		return (1);
	while (un != 0)
	{
		un /= 10;
		len++;
	}
	return (len);
}

char	*ft_utoa(unsigned int n)
{
	char	*nbrfinal;
	int		nbrlen;

	nbrlen = ft_unbrlen(n);
	nbrfinal = (char *)malloc(sizeof(char) * (nbrlen + 1));
	if (!nbrfinal)
		return (0);
	nbrfinal[nbrlen] = '\0';
	nbrlen--;
	while (nbrlen >= 0)
	{
		nbrfinal[nbrlen] = n % 10 + 48;
		n /= 10;
		nbrlen--;
	}
	return (nbrfinal);
}

int	ft_print_uint(unsigned int un)
{
	int		char_count;
	char	*output;

	char_count = 0;
	output = ft_utoa(un);
	ft_putstr_fd(output, 1);
	char_count = ft_strlen(output);
	free(output);
	return (char_count);
}

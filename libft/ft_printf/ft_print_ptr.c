/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:49:49 by znogueir          #+#    #+#             */
/*   Updated: 2022/05/17 18:20:06 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptrsize(unsigned long long np)
{
	int	size;

	size = 0;
	if (np == 0)
		return (1);
	while (np > 0)
	{
		np /= 16;
		size++;
	}
	return (size);
}

char	*ft_ptrtohex(unsigned long long np)
{
	int			xlen;
	char		*hexnbr;

	xlen = ft_ptrsize(np);
	hexnbr = malloc(sizeof(char) * (xlen + 1));
	if (!hexnbr)
		return (0);
	hexnbr[xlen] = '\0';
	xlen--;
	while (xlen >= 0)
	{
		hexnbr[xlen] = "0123456789abcdef"[np % 16];
		np /= 16;
		xlen--;
	}
	return (hexnbr);
}

int	ft_print_ptr(unsigned long long ptr)
{
	char				*output;
	int					char_count;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	output = ft_ptrtohex(ptr);
	ft_putstr_fd(output, 1);
	char_count = ft_strlen(output);
	free(output);
	return (char_count + 2);
}

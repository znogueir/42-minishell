/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:49:49 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/29 22:09:19 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"


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
		ft_putstr_fd("(nil)", 1); //write to stderr
		return (5);
	}
	ft_putstr_fd("0x", 1); //write to stderr
	output = ft_ptrtohex(ptr);
	ft_putstr_fd(output, 1); //write to stderr
	char_count = ft_strlen(output);
	free(output);
	return (char_count + 2);
}

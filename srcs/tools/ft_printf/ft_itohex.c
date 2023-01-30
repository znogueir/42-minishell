/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:05:42 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/30 17:42:21 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"

int	ft_nhexlen(unsigned int n)
{
	int	xlen;

	xlen = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		xlen++;
	}
	return (xlen);
}

char	*ft_itohex(unsigned int n, char c)
{
	int			xlen;
	char		*hexnbr;

	xlen = ft_nhexlen(n);
	hexnbr = ft_malloc(NULL, sizeof(char) * (xlen + 1));
	if (!hexnbr)
		return (0);
	hexnbr[xlen] = '\0';
	xlen--;
	while (xlen >= 0)
	{
		hexnbr[xlen] = "0123456789abcdef"[n % 16];
		n /= 16;
		if (ft_isalpha(hexnbr[xlen]) && c == 'X')
			hexnbr[xlen] = ft_toupper(hexnbr[xlen]);
		xlen--;
	}
	return (hexnbr);
}

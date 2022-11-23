/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_basics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:24:06 by znogueir          #+#    #+#             */
/*   Updated: 2022/07/06 14:24:12 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *s)
{
	if (s)
		return (write(1, s, ft_strlen(s)));
	return (write(1, "(null)", 6));
}

int	ft_print_int(int n)
{
	ft_putnbr_fd(n, 1);
	return (ft_nbrlen(n));
}

int	ft_print_hexa(unsigned int n, char c)
{
	char	*hexnbr;

	hexnbr = ft_itohex(n, c);
	ft_putstr_fd(hexnbr, 1);
	free(hexnbr);
	return (ft_nhexlen(n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:12:43 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/30 21:18:00 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(t_data *data, int n)
{
	char		*nbrfinal;
	long int	ln;
	int			neg;
	int			nbrlen;

	nbrlen = ft_nbrlen(n);
	nbrfinal = ft_malloc(data, sizeof(char) * (nbrlen + 1));
	if (!nbrfinal)
		return (0);
	ln = n;
	neg = ft_isneg(n);
	nbrfinal[nbrlen] = '\0';
	nbrlen--;
	if (ln < 0)
	{
		ln *= -1;
		nbrfinal[0] = '-';
	}
	while (nbrlen >= neg)
	{
		nbrfinal[nbrlen] = ln % 10 + 48;
		ln /= 10;
		nbrlen--;
	}
	return (nbrfinal);
}

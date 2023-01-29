/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:45:39 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/29 22:09:26 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"

int	ft_sorting(char c, va_list arg_list)
{
	int	chr_count;

	chr_count = 0;
	if (c == 'c')
		chr_count = ft_print_char(va_arg(arg_list, int));
	else if (c == 's')
		chr_count = ft_print_str(va_arg(arg_list, char *));
	else if (c == 'p')
		chr_count = ft_print_ptr(va_arg(arg_list, long long unsigned int));
	else if (c == 'd' || c == 'i')
		chr_count = ft_print_int(va_arg(arg_list, int));
	else if (c == 'u')
		chr_count = ft_print_uint(va_arg(arg_list, unsigned int));
	else if (c == 'x' || c == 'X')
		chr_count = ft_print_hexa(va_arg(arg_list, unsigned int), c);
	else if (c == '%')
		chr_count += ft_print_char('%');
	return (chr_count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		wrtn_char;
	va_list	arg_list;

	va_start(arg_list, s);
	i = 0;
	wrtn_char = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (!s[i + 1])
				break ;
			wrtn_char += ft_sorting(s[i + 1], arg_list);
			i++;
		}
		else
			wrtn_char += ft_print_char(s[i]);
		i++;
	}
	va_end(arg_list);
	return (wrtn_char);
}

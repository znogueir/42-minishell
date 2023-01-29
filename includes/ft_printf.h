/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:47:59 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/29 22:07:33 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "minishell.h"

//	get nbrlen
int		ft_nbrlen(int n);
int		ft_unbrlen(unsigned int un);
int		ft_nhexlen(unsigned int n);
//	print basics
int		ft_print_char(char c);
int		ft_print_str(char *s);
int		ft_print_int(int n);
int		ft_print_ptr(unsigned long long ptr);
//	conversions
char	*ft_utoa(unsigned int n);
char	*ft_itohex(unsigned int n, char c);
//	print advanced
int		ft_print_uint(unsigned int un);
int		ft_print_hexa(unsigned int n, char c);
//	main functions
int		ft_sorting(char c, va_list arg_list);
int		ft_printf(const char *s, ...);

#endif

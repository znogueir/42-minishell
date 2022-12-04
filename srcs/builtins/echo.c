/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:21:35 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/04 17:40:48 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char *str, int newline)
{
	ft_printf("test cmd : echo -> '%s'", str);
	if (newline)
		write(1, "\n", 1);
	return (0);
}

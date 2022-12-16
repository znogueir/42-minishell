/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:51:08 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
{
	char	end_quote;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != 39 && str[i] != 34)
		i++;
	if (str[i] == 39 || str[i] == 34)
		end_quote = str[i];
	else
		return (0);
	i++;
	while (str[i] && str[i] != end_quote)
		i++;
	if (!str[i])
		return (1);
	return (check_quote(str + i + 1));
}

int	check_errors(char *line)
{
	if (check_quote(line))
	{
		write_error("syntax error: quote missing\n");
		return (1);
	}
	return (0);
}

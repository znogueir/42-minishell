/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:07 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 20:03:13 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_overflow(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-' && str[i + (str[0] == '+' || str[0] == '-')] \
		> "9223372036854775808"[i])
			return (0);
		if (str[0] != '-' && str[i + (str[0] == '+' || str[0] == '-')] \
		> "9223372036854775807"[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_num(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		if (i > 18 + (str[0] == '+' || str[0] == '-'))
			return (0);
		i++;
	}
	if (ft_strlen(str + (str[0] == '+' || str[0] == '-')) < 19)
		return (1);
	return (check_overflow(str));
}

int	ft_exit(t_data *data, char **cmd)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd[1])
	{
		if (is_num(cmd[1]))
		{
			if (cmd[2])
				return (ft_putstr_fd("minishell: exit: \
too many arguments\n", 2), 1);
			g_exit = (char)ft_atoi(cmd[1]);
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_exit = 2;
		}
	}
	dup2(data->insave, 0);
	dup2(data->outsave, 1);
	//ft_exit_fork(data, cmd, g_exit);
	ft_malloc(NULL, data, -777, 0);
	return (g_exit);
}
// check for long long int overflows 
//-> minishell: exit: "nbr": numeric argument required;

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:07 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/19 02:50:55 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
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
			else if (ft_atoi(cmd[1]) > 255)
				g_exit = ft_atoi(cmd[1]) % 256;
			else
				g_exit = ft_atoi(cmd[1]);
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
	ft_exit_fork(data, cmd, g_exit);
	return (g_exit);
}

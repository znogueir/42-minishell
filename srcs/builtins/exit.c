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
	// (void)data;
	// (void)cmd;
	//ft_printf("bye! 👋\n");
	ft_putstr_fd("exit\n", 2);
	dup2(data->insave, 0);
	dup2(data->outsave, 1);
	ft_exit_fork(data, cmd, g_exit);
	return (g_exit);
	// ft_printf("exit\n");
}

/*
if (cmd[1])
	is_num : g_exit = atoi; -> exit;
	is_num > 255 : g_exit = atoi % 256; -> exit;
	!is_num : print "numeric argument required", g_exit = 2; -> exit;
if (cmd[1] && cmd[2])
	is_num (cmd[1]) : print "too many arguments", g_exit = 1; -> dont exit;
	!is_num : print "numeric argument required", g_exit = 2; -> exit;
*/

/*
if (cmd[1])
{
	if (is_num(cmd[1]))
	{
		if (cmd[2])
			print "too many arguments", g_exit = 1; -> dont exit;
		else if (ft_atoi(cmd[1]) > 255)
			g_exit = atoi % 256; -> exit;
		else
			g_exit = atoi; -> exit;
	}
	else
		print "numeric argument required", g_exit = 2; -> exit;
}*/
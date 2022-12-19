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

int	ft_exit(t_data *data, char **cmd)
{
	// (void)data;
	// (void)cmd;
	//ft_printf("bye! 👋\n");
	ft_putstr_fd("exit\n", 2);
	dup2(data->insave, 0);
	dup2(data->outsave, 1);
	g_exit = 127;
	ft_exit_fork(data, cmd, g_exit);
	return (g_exit);
	// ft_printf("exit\n");
}

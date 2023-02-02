/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:33:02 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/02 19:00:37 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_in_fork(int sig)
{
	if (sig == SIGINT)
		g_exit = 130;
	else if (sig == SIGQUIT)
		g_exit = 131;
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit = 130;
	}
}

void	handle_sig_heredocs(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		ft_close(&fd);
		ft_putstr_fd("\n", 1);
		g_exit = 257;
	}
}

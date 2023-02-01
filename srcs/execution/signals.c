/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:33:02 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 22:47:14 by yridgway         ###   ########.fr       */
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

// printf("\nchild\n");
// fd = open("/dev/null", O_RDONLY);
// dup2(fd, 0);
// ft_close(&fd);
// write(0, "\0", 1);

// int	error_here_doc(t_exec *exec, int stdin_fd)
// {
// 	if (g_exit == 257)
// 	{
// 		// heredoc_rm(exec->tok_lst);
// 		dup2(stdin_fd, 0);
// 		ft_close(&stdin_fd);
// 		g_exit = 130;
// 		return (1);
// 	}
// 	return (0);
// }

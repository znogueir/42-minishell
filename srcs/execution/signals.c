/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:33:02 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/15 17:53:50 by yridgway         ###   ########.fr       */
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

// HEREDOCS
void	handle_sig_heredocs(int sig)
{
	// int	fd;

	// ft_putstr_fd("sig_handling\n", 2);
	if (sig == SIGINT)
	{
		// ft_putstr_fd("BANANA\n", 2);
		// fd = open("/dev/null", O_RDONLY);
		// dup2(fd, 0);
		// close(fd); 
		close(0);
		ft_putstr_fd("tagada", 2);
		ft_putstr_fd("\n", 1);
		g_exit = 257;
		// ft_printf("%d\n", g_exit);
	}
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

// ft_printf("\nchild\n");
// fd = open("/dev/null", O_RDONLY);
// dup2(fd, 0);
// close(fd);
// write(0, "\0", 1);

// int	error_here_doc(t_exec *exec, int stdin_fd)
// {
// 	if (g_exit == 257)
// 	{
// 		// heredoc_rm(exec->tok_lst);
// 		dup2(stdin_fd, 0);
// 		close(stdin_fd);
// 		g_exit = 130;
// 		return (1);
// 	}
// 	return (0);
// }

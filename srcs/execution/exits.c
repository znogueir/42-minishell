/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:27:36 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/02 20:52:53 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_permission_denied(char *prog)
{
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(prog, 2);
	write(2, "\n", 1);
	return (126);
}

int	ft_command_not_found(char *prog)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	if (prog)
		ft_putstr_fd(prog, 2);
	write(2, "\n", 1);
	return (127);
}

int	ft_no_such_file(char *prog)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	if (prog)
		ft_putstr_fd(prog, 2);
	write(2, "\n", 1);
	return (127);
}

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	ft_is_directory(char *prog)
{
	if (!is_directory(prog))
		return (0);
	ft_putstr_fd("minishell: Is a directory: ", 2);
	if (prog)
		ft_putstr_fd(prog, 2);
	write(2, "\n", 1);
	g_exit = 126;
	return (126);
}

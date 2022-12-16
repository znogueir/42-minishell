/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:27:36 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_permission_denied(char *prog)
{
	ft_putstr_fd("pipex: permission denied: ", 2);
	ft_putstr_fd(prog, 2);
	write(2, "\n", 1);
	return (126);
}

int	ft_command_not_found(char *prog)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	if (prog)
		ft_putstr_fd(prog, 2);
	write(2, "\n", 1);
	return (127);
}

int	ft_no_such_file(char *prog)
{
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	if (prog)
		ft_putstr_fd(prog, 2);
	write(2, "\n", 1);
	return (127);
}

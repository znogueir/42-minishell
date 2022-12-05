/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:55:39 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/05 01:36:24 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_valid_cmd(char **command, char **env, int *ext)
{
	char	*validcmd;

	if (!command || !command[0])
		validcmd = NULL;
	else if (command[0][0] == '.' || command[0][0] == '/'
		|| command[0][1] == '/')
	{
		validcmd = ft_strdup(command[0]);
		*ext = check_path(validcmd, validcmd);
		if (*ext == 1)
			*ext = ft_no_such_file(validcmd);
	}
	else
		validcmd = get_valid_path(env, command);
	return (validcmd);
}

void	ft_execute(char **command, char **env)
{
	char	*validcmd;
	int		ext;

	ext = 1;
	validcmd = get_valid_cmd(command, env, &ext);
	if (validcmd == NULL)
	{
		ft_free_arr(command);
		ext = ft_command_not_found(validcmd);
		exit(ext);
	}
	// ft_putstr_fd("\n\n", 2);
	// ft_putstr_fd(validcmd, 2);
	// ft_putstr_fd("\n\n", 2);
	// ft_putstr_fd(command[0], 2);
	// ft_putstr_fd("\n\n", 2);
	if (execve(validcmd, command, env) == -1)
	{
		free(validcmd);
		unlink(".temp_heredoc");
		ft_free_arr(command);
		exit(ext);
	}
}

void	ft_child(char **cmd, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_exit_msg("problem with pipe()");
	pid = fork();
	if (pid == -1)
		ft_exit_msg("problem with fork()");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_execute(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

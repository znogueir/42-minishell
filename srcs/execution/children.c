/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:55:39 by yridgway          #+#    #+#             */
/*   Updated: 2022/11/10 22:43:22 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_execute(char *cmd, char **env)
{
	char	**command;
	char	*validcmd;
	int		ext;

	ext = 1;
	command = ft_split(cmd, " ");
	validcmd = get_valid_cmd(command, env, &ext);
	if (validcmd == NULL)
	{
		ft_free_arr(command);
		ext = ft_command_not_found(validcmd);
		exit(ext);
	}
	if (execve(validcmd, command, env) == -1)
	{
		free(validcmd);
		unlink(".temp_heredoc");
		ft_free_arr(command);
		exit(ext);
	}
}

void	ft_child(char *cmd, char **env)
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

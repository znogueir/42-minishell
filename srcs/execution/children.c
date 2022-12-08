/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:55:39 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/08 19:43:07 by yridgway         ###   ########.fr       */
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
	// if (is_builtin(command))
	// 	execute_builtins(command);
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

void	ft_pipe(t_cmdtable *table, char **cmd, char **env)
{
	int			fd[2];
	pid_t		pid;
	t_filelist	*infile;
	t_filelist	*outfile;

	infile = file_get_last(table->infile);
	outfile = file_get_last(table->outfile);
	if (pipe(fd) == -1)
		ft_exit_msg("problem with pipe()");
	pid = fork();
	if (pid == -1)
		ft_exit_msg("problem with fork()");
	if (pid == 0)
	{
		if (infile->fd != 0)
			dup2(infile->fd, 0);
		if (outfile->fd != 1)
			dup2(outfile->fd, 1);
		else if (infile->fd == 0)
		{
			close(fd[0]);
			if (table->next)
				dup2(fd[1], 1);
		}
		ft_execute(cmd, env);
	}
	waitpid(0, NULL, 0);
	if (outfile->fd == 1 && infile->fd == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
	ft_free_arr(cmd);
}

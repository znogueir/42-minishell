/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:55:39 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/08 22:00:31 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	convert_env(t_data *data, t_env *loc_env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = loc_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	data->char_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (loc_env)
	{
		data->char_env[i++] = ft_strjoin(ft_strjoin(ft_strdup(loc_env->name), \
		"="), loc_env->content);
		loc_env = loc_env->next;
	}
	data->char_env[i] = NULL;
}

char	*get_valid_cmd(t_data *data, char **command, int *ext)
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
		validcmd = get_valid_path(data, command);
	return (validcmd);
}

void	ft_execute(t_data *data, char **command)
{
	char	*validcmd;
	int		ext;

	ext = 1;
	if (exec_builtin(command, data))
	{
		free_table(data->cmdtable);
		free_all(data);
		free_split(command);
		exit(0);
	}
	convert_env(data, data->loc_env);
	validcmd = get_valid_cmd(data, command, &ext);
	if (validcmd == NULL)
	{
		free_split(command);
		ext = ft_command_not_found(validcmd);
		exit(ext);
	}
	if (execve(validcmd, command, data->char_env) == -1)
	{
		free(validcmd);
		unlink(".temp_heredoc");
		free_split(command);
		exit(ext);
	}
}

void	ft_pipe(t_data *data, t_cmdtable *table, char **cmd)
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
		ft_execute(data, cmd);
	}
	waitpid(0, NULL, 0);
	if (outfile->fd == 1 && infile->fd == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
	free_split(cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:55:39 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/11 02:31:20 by yridgway         ###   ########.fr       */
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

void	ft_execute(t_data *data, char **command)
{
	char	*validcmd;
	int		ext;

	ext = 1;
	if (exec_builtin(command, data))
	{
		// close(data->pipe[1]);
		// close(data->pipe[0]);
		ft_exit_fork(data, command, 1);
	}
	convert_env(data, data->loc_env);
	validcmd = get_valid_cmd(data, command, &ext);
	if (validcmd == NULL)
	{
		ext = ft_command_not_found(validcmd);
		ft_exit_fork(data, command, 1);
	}
	execve(validcmd, command, data->char_env);
	free(validcmd);
	ft_exit_fork(data, command, 1);
}

void	ft_open_redirs(t_data *data, t_cmdtable *table)
{
	t_filelist	*infile;
	t_filelist	*outfile;

	infile = file_get_last(table->infile);
	outfile = file_get_last(table->outfile);
	if (infile->fd != 0)
		dup2(infile->fd, 0);
	if (outfile->fd != 1)
		dup2(outfile->fd, 1);
	else if (infile->fd == 0)
	{
		if (table->next)
			dup2(data->pipe[1], 1);
	}
}

void	ft_execute_pipes(t_data *data, t_cmdtable *table, char **cmd)
{
	data->pid = fork();
	if (data->pid == -1)
		ft_exit_msg("problem with fork()");
	if (data->pid == 0)
	{
		close(data->pipe[0]);
		ft_open_redirs(data, table);
		ft_execute(data, cmd);
	}
	waitpid(0, NULL, 0);
}

void	ft_execute_alone(t_data *data, t_cmdtable *table, char **cmd)
{
	int			insave;
	int			outsave;
	t_filelist	*infile;
	t_filelist	*outfile;

	infile = file_get_last(table->infile);
	outfile = file_get_last(table->outfile);
	insave = dup(0);
	outsave = dup(1);
	// close(data->pipe[1]);
	// close(data->pipe[0]);
	if (infile->fd != 0)
		dup2(infile->fd, 0);
	if (outfile->fd != 1)
		dup2(outfile->fd, 1);
	exec_builtin(cmd, data);
	ft_close_fds(table);
	dup2(insave, 0);
	dup2(outsave, 1);
	close(insave);
	close(outsave);
}

void	ft_pipe(t_data *data, t_cmdtable *table, char **cmd)
{
	t_filelist	*infile;
	t_filelist	*outfile;

	infile = file_get_last(table->infile);
	outfile = file_get_last(table->outfile);
	if (pipe(data->pipe) == -1)
		ft_exit_msg("problem with pipe()");
	if (is_builtin(cmd) && data->cmdtable->next != NULL)
		ft_execute_alone(data, table, cmd);
	else
		ft_execute_pipes(data, table, cmd);
	close(data->pipe[1]);
	if (outfile->fd == 1 && infile->fd == 0)
		dup2(data->pipe[0], 0);
	free_split(cmd);
}

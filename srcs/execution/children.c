/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:55:39 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/22 00:35:26 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	g_exit = 1;
	if (command[0] && is_builtin(command))
	{
		g_exit = exec_builtin(command, data);
		ft_exit_fork(data, command, g_exit);
	}
	convert_env(data, data->loc_env);
	// printf("command[0] %c\n", command[0]);
	if (command && command[0] && !command[0][0])
		validcmd = NULL;
	else
		validcmd = get_valid_cmd(data, command, &g_exit);
	// printf("valid: %s\n", validcmd);
	if (validcmd == NULL)
	{
		g_exit = ft_command_not_found(validcmd);
		ft_exit_fork(data, command, g_exit);
	}
	execve(validcmd, command, data->char_env);
	free(validcmd);
	ft_exit_fork(data, command, g_exit);
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
	if (outfile->fd == 1)
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
	// ft_pidadd_back(&data->process, data->pid);
	table->pid = data->pid;
	signal(SIGINT, sig_in_fork);
	signal(SIGQUIT, sig_in_fork);
	if (data->pid == 0)
	{
		close(data->pipe[0]);
		ft_open_redirs(data, table);
		if (cmd)
			ft_execute(data, cmd);
		ft_exit_fork(data, cmd, g_exit);
	}
}

void	ft_execute_alone(t_data *data, t_cmdtable *table, char **cmd)
{
	t_filelist	*infile;
	t_filelist	*outfile;

	infile = file_get_last(table->infile);
	outfile = file_get_last(table->outfile);
	if (infile->fd != 0)
		dup2(infile->fd, 0);
	if (outfile->fd != 1)
		dup2(outfile->fd, 1);
	g_exit = exec_builtin(cmd, data);
	ft_close_fds(data);
}

void	ft_pipe(t_data *data, t_cmdtable *table, char **cmd)
{
	// t_filelist	*infile;
	// t_filelist	*outfile;

	// infile = file_get_last(table->infile);
	// outfile = file_get_last(table->outfile);
	if (pipe(data->pipe) == -1)
		ft_exit_msg("problem with pipe()");
	data->open_pipe = 1;
	// if (!cmd)
	// 	return ;
	if (cmd && cmd[0] && is_builtin(cmd) && !data->cmdtable->next)
		ft_execute_alone(data, table, cmd);
	else if (cmd)
	{
		ft_execute_pipes(data, table, cmd);
	}
	close(data->pipe[1]);
	//if (outfile->fd == 1 && infile->fd == 0)
	dup2(data->pipe[0], 0);
	free_split(cmd);
}

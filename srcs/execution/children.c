/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:55:39 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/01 20:21:30 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_data *data, char **command)
{
	char	*validcmd;

	g_exit = 1;
	if (command[0] && is_builtin(command))
	{
		g_exit = exec_builtin(command, data);
		// ft_exit_fork(data, command, g_exit);
		ft_malloc(NULL, data, -777, 0);
	}
	convert_env(data, data->loc_env);
	update_env(data->char_env, data);
	if (command && command[0] && !command[0][0])
		validcmd = NULL;
	else
		validcmd = get_valid_cmd(data, command, &g_exit);
	if (validcmd == NULL)
	{
		g_exit = ft_command_not_found(validcmd);
		// ft_exit_fork(data, command, g_exit);
		ft_malloc(NULL, data, -777, 0);
	}
	execve(validcmd, command, data->char_env);
	ft_free(validcmd);
	// ft_exit_fork(data, command, g_exit);
	ft_malloc(NULL, data, -777, 0);
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

int	ft_execute_pipes(t_data *data, t_cmdtable *table, char **cmd)
{
	data->pid = fork();
	if (data->pid == -1)
		return (ft_putstr_fd("problem with fork()\n", 2), \
		ft_malloc(NULL, data, -777, 0), 1);
	table->pid = data->pid;
	signal(SIGINT, sig_in_fork);
	signal(SIGQUIT, sig_in_fork);
	if (data->pid == 0)
	{
		close(data->pipe[0]);
		ft_open_redirs(data, table);
		if (cmd)
			ft_execute(data, cmd);
		// ft_exit_fork(data, cmd, g_exit);
		ft_malloc(NULL, data, -777, 0);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
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
	ft_close_fds(data, infile, outfile);
}

int	ft_pipe(t_data *data, t_cmdtable *table, char **cmd)
{
	if (pipe(data->pipe) == -1)
		return (ft_putstr_fd("problem with pipe()\n", 2), \
		ft_malloc(NULL, data, -777, 0), 1);
	data->open_pipe = 1;
	if (cmd && cmd[0] && is_builtin(cmd) && !data->cmdtable->next)
		ft_execute_alone(data, table, cmd);
	else if (cmd)
	{
		ft_execute_pipes(data, table, cmd);
	}
	close(data->pipe[1]);
	dup2(data->pipe[0], 0);
	// free_split(cmd);
	return (0);
}

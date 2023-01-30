/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:46:37 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/30 22:45:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_data *data)
{
	int			status;
	t_cmdtable	*table;

	table = data->cmdtable;
	while (table)
	{
		if (table->pid > -1)
		{
			waitpid(table->pid, &status, 0);
			if (WTERMSIG(status) == 2)
				ft_putchar_fd('\n', 1);
			else if (WTERMSIG(status) == 3)
				ft_putstr_fd("Quit (core dumped)\n", 1);
			if (WIFEXITED(status))
				g_exit = WEXITSTATUS(status);
			if (g_exit == 258)
				printf("yo mama so fat she cant be malloc'd");
		}
		table = table->next;
	}
}

int	ft_pipex(t_data *data)
{
	t_cmdtable	*table;

	table = data->cmdtable;
	if (!table)
		return (0);
	ft_check_fds(table);
	close(data->insave);
	data->insave = dup(0);
	close(data->outsave);
	data->outsave = dup(1);
	while (table)
	{
		if (table->status)
			ft_pipe(data, table, ft_arr_dup(data, table->cmd));
		table = table->next;
		ft_close_pipes(data);
	}
	ft_wait(data);
	ft_close_fds(data, NULL, NULL);//in, out);
	dup2(data->insave, 0);
	dup2(data->outsave, 1);
	// close(data->insave);
	// close(data->outsave);
	return (1);
}

int	ft_executor(t_data *data, char **env)
{
	(void)env;
	data->cmdtable = NULL;
	if (make_cmdtable(data))
		return (free_table(data, data->cmdtable), 1);
	ft_pipex(data);
	free_table(data, data->cmdtable);
	return (0);
}

//echo banana < in | ls < bingf | < bing
//<< EOF << banana >out1(nopermissions) ls -la <in <<yo <jfksj
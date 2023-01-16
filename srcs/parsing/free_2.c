/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:08:28 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/16 18:52:59 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmdline *cmd)
{
	t_cmdline	*prev;

	while (cmd)
	{
		prev = cmd;
		cmd = cmd->next;
		free(prev->content);
		free(prev);
	}
}

void	free_env(t_env *loc_env)
{
	t_env	*prev;

	while (loc_env)
	{
		prev = loc_env;
		loc_env = loc_env->next;
		free(prev->name);
		free(prev->content);
		free(prev);
	}
}

void	free_files(t_filelist *filelist)
{
	t_filelist	*prev;

	while (filelist)
	{
		prev = filelist;
		filelist = filelist->next;
		if (prev->type == H_DOC)
			unlink(prev->filename);
		free(prev->filename);
		free(prev);
	}
}

void	free_table(t_data *data, t_cmdtable *table)
{
	t_cmdtable	*prev;

	while (table)
	{
		// while (data->hdoc_write--)
		close(data->insave);
		prev = table;
		table = table->next;
		free_files(prev->infile);
		free_files(prev->outfile);
		free_split(prev->cmd);
		free(prev);
	}
}

// void	free_process(t_process *process)
// {
// 	t_process	*prev;

// 	while (process)
// 	{
// 		prev = process;
// 		process = process->next;
// 		free(prev);
// 	}
// }
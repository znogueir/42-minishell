/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:08:28 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 20:28:08 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

void	free_cmd(t_cmdline *cmd)
{
	t_cmdline	*prev;

	while (cmd)
	{
		prev = cmd;
		cmd = cmd->next;
		ft_free(prev->content);
		ft_free(prev);
	}
}

void	free_env(t_env *loc_env)
{
	t_env	*prev;

	while (loc_env)
	{
		prev = loc_env;
		loc_env = loc_env->next;
		ft_free(prev->name);
		ft_free(prev->content);
		ft_free(prev);
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
		ft_free(prev->filename);
		ft_free(prev);
	}
}

void	free_table(t_data *data, t_cmdtable *table)
{
	t_cmdtable	*prev;

	while (table)
	{
		prev = table;
		table = table->next;
		free_files(prev->infile);
		free_files(prev->outfile);
		free_split(prev->cmd);
		ft_free(prev);
	}
	data->cmdtable = NULL;
}

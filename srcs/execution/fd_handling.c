/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:46:37 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/01 22:47:05 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_fds(t_cmdtable *table)
{
	t_filelist	*infile;
	t_filelist	*outfile;

	while (table && table->status)
	{
		infile = file_get_last(table->infile);
		outfile = file_get_last(table->outfile);
		if (!infile || !outfile || (outfile->fd != -1 && infile->fd != -1))
		{
			table->status = 1;
			table = table->next;
			continue ;
		}
		else if (outfile->fd == -1)
			perror(outfile->filename);
		else
			perror(infile->filename);
		table->status = 0;
		g_exit = 1;
		table = table->next;
	}
}

void	ft_close_pipes(t_data *data)
{
	if (data->open_pipe)
	{
		if (data->pipe[0] != -1)
			ft_close(&data->pipe[0]);
		if (data->pipe[1] != -1)
			ft_close(&data->pipe[1]);
	}
	data->open_pipe = 0;
}

void	ft_close_fds(t_data *data, t_filelist *in, t_filelist *out)
{
	t_cmdtable	*tab;

	tab = data->cmdtable;
	while (tab)
	{
		if (!tab || !tab->infile || !tab->outfile)
			break ;
		in = tab->infile;
		out = tab->outfile;
		while (in)
		{
			if (in->fd > 2)
				ft_close(&in->fd);
			in = in->next;
		}
		while (out)
		{
			if (out->fd > 2)
				ft_close(&out->fd);
			out = out->next;
		}
		if (tab)
			tab = tab->next;
	}
	ft_close_pipes(data);
}

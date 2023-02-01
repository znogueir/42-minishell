/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:50:19 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/01 20:37:38 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_count(t_cmdline *line)
{
	int	count;

	count = 0;
	while (line && line->type != NEWLINES && line->type != PIPE)
	{
		while (line && !line->content)
			line = line->next;
		while (line && is_redir(line->type))
			line = line->next->next;
		if (line && line->content && line->type == WORD)
		{
			line = line->next;
			count++;
		}
	}
	return (count);
}

void	ft_make_cmd_array(t_data *data, t_cmdtable *table, t_cmdline *cmdline)
{
	int			i;
	int			count;

	i = 0;
	count = ft_cmd_count(cmdline);
	if (count == 0)
	{
		table->cmd = NULL;
		return ;
	}
	table->cmd = ft_malloc(NULL, data, sizeof(char *) * (count + 1));
	while (cmdline && i < count)
	{
		if (!cmdline->content)
			cmdline = cmdline->next;
		else if (is_redir(cmdline->type))
			cmdline = cmdline->next->next;
		else
		{
			table->cmd[i++] = ft_strdup(data, cmdline->content);
			cmdline = cmdline->next;
		}
	}
	table->cmd[i] = NULL;
}

int	ft_init_cmdtable(t_data *data)
{
	t_cmdline	*line;

	line = data->cmd;
	ft_tableadd_back(&data->cmdtable, ft_tablenew(data));
	while (line && line->type != NEWLINES)
	{
		if (line && line->type == PIPE)
			ft_tableadd_back(&data->cmdtable, ft_tablenew(data));
		line = line->next;
	}
	line = data->cmd;
	return (ft_here_doc(data, line));
}

int	make_cmdtable(t_data *data)
{
	t_cmdline	*line;
	t_cmdtable	*table;

	if (!ft_init_cmdtable(data))
		return (1);
	line = data->cmd;
	table = data->cmdtable;
	while (line && table)
	{
		if (line && line->type == PIPE)
			line = line->next;
		ft_make_cmd_array(data, table, line);
		table->status = ft_fill_files(data, table, line);
		while (line && line->type != PIPE)
			line = line->next;
		table = table->next;
	}
	data->hdoc_open = 0;
	data->hdoc_write = 0;
	return (0);
}

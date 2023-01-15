/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:50:19 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/15 19:32:26 by yridgway         ###   ########.fr       */
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
		if (line && (!line->content || is_redir(line->type)))
		{
			while (line && is_redir(line->type))
				line = line->next->next;
			// if (line)
			// 	line = line->next;
			while (line && !line->content)
				line = line->next;
		}
		if (line && line->content && line->type == WORD)
			count++;
		if (line)
			line = line->next;
	}
	return (count);
}

void	ft_make_cmd_array(t_cmdtable *table, t_cmdline *cmdline)
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
	table->cmd = malloc(sizeof(char *) * (count + 1));
	while (cmdline && i < count)
	{
		if (!cmdline->content)
		{
			cmdline = cmdline->next;
			continue ;
		}
		if (is_redir(cmdline->type))
			cmdline = cmdline->next->next;
		else
		{
			table->cmd[i++] = ft_strdup(cmdline->content);
			cmdline = cmdline->next;
		}
	}
	table->cmd[i] = NULL;
}

int	ft_here_doc(t_data *data, t_cmdline *cmdline)
{
	int	h_doc;

	h_doc = 1;
	while (cmdline) // && cmdline->type != NEWLINES)
	{
		if (cmdline->type == H_DOC)
			h_doc = \
			ft_here_doc_write(data, cmdline->next->content, data->hdoc_write++);
		cmdline = cmdline->next;
	}
	return (h_doc);
}

int	ft_fill_files(t_data *data, t_cmdtable *table, t_cmdline *cmdline)
{
	t_cmdline	*line;
	int			open;
	int			i;

	line = cmdline;
	ft_fileadd_back(&table->infile, ft_filenew(0, ft_strdup(IN), LESS, -1));
	ft_fileadd_back(&table->outfile, ft_filenew(1, ft_strdup(OUT), GREAT, -1));
	i = 0;
	open = 1;
	while (open && line && line->type != PIPE)
	{
		while (line && !line->content)
			line = line->next;
		if (!line)
			break ;
		if (open && line->type == LESS)
			open = ft_infile_open(table, line, i++);
		if (open && line->type == GREAT)
			open = ft_outfile_open(table, line, \
			O_RDWR | O_CREAT | O_TRUNC, i++);
		if (open && line->type == H_DOC)
			open = ft_here_doc_open(table, line, i++, data->hdoc_open++);
		if (open && line->type == APPEND)
			open = ft_outfile_open(table, line, \
			O_RDWR | O_CREAT | O_APPEND, i++);
		line = line->next;
	}
	if (open == 0)
		g_exit = 1;
	return (open);
}

int	ft_init_cmdtable(t_data *data)
{
	t_cmdline	*line;

	line = data->cmd;
	ft_tableadd_back(&data->cmdtable, ft_tablenew());
	while (line && line->type != NEWLINES)
	{
		if (line && line->type == PIPE)
			ft_tableadd_back(&data->cmdtable, ft_tablenew());
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
		ft_make_cmd_array(table, line);
		table->status = ft_fill_files(data, table, line);
		while (line && line->type != PIPE)
			line = line->next;
		table = table->next;
	}
	data->hdoc_open = 0;
	data->hdoc_write = 0;
	return (0);
}

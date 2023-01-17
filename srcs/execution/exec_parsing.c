/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:50:19 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/15 19:01:01 by yridgway         ###   ########.fr       */
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
	// printf("line: %s, count: %d\n", cmdline->content, count);
	if (count == 0)
	{
		table->cmd = NULL;
		return ;
	}
	table->cmd = ft_mallocator(data, sizeof(char *) * (count + 1));
	while (cmdline && i < count)
	{
		if (!cmdline->content)
		{
			cmdline = cmdline->next;
			continue ;
		}
		if (is_redir(cmdline->type))
			cmdline = cmdline->next->next;
		// if (cmdline->type == H_DOC || cmdline->type == APPEND)
		// 	cmdline = cmdline->next;
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
	int	open;

	h_doc = 1;
	open = 1;
	while (cmdline && cmdline->type != NEWLINES && cmdline->type != PIPE)
	{
		if (cmdline->type == H_DOC)
			h_doc = \
			ft_here_doc_write(data, cmdline->next->content, data->hdoc_write++);
		if (!h_doc)
			open = h_doc;
		cmdline = cmdline->next;
	}
	return (open);
}

int	ft_fill_files(t_data *data, t_cmdtable *table, t_cmdline *cmdline)
{
	t_cmdline	*line;
	int			open;
	int			i;

	line = cmdline;
	open = ft_here_doc(data, cmdline);
	ft_fileadd_back(&table->infile, ft_filenew(0, ft_strdup(IN), LESS, -1));
	ft_fileadd_back(&table->outfile, ft_filenew(1, ft_strdup(OUT), GREAT, -1));
	i = 0;
	while (open && line && line->type != NEWLINES && line->type != PIPE)
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

int	make_cmdtable(t_data *data)
{
	t_cmdline	*line;
	t_cmdline	*temp;
	t_cmdtable	*cur_tab;

	line = data->cmd;
	// ft_pop_nulls(data);
	// print_list(data->cmd);
	//g_exit = ft_parser(data);
	//if (g_exit)
	//	return (1);
	// w
	while (line && line->type != NEWLINES)
	{
		while (line && !line->content)
			line = line->next;
		//printf("line: %s\n", line->content);
		ft_tableadd_back(&data->cmdtable, ft_tablenew());
		cur_tab = get_last(data->cmdtable);
		temp = line;
		cur_tab->status = ft_fill_files(data, cur_tab, line);
		ft_make_cmd_array(cur_tab, temp);
		while (line && line->type != PIPE)
			line = line->next;
		if (line)
			line = line->next;
	}
	data->hdoc_open = 0;
	data->hdoc_write = 0;
	// display_cmdtable(data->cmdtable);
	return (0);
}

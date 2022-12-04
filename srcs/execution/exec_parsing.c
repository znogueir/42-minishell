/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:50:19 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/04 23:06:25 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_count(t_cmdline *line)
{
	int	count;

	count = 0;
	while (line && line->type != NEWLINES && line->type != PIPE)
	{
		if (is_redir(line->type))
			line = line->next;
		else
			count++;
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
	table->cmd = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
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

int	ft_here_doc(t_cmdline *cmdline)
{
	int	h_doc;
	int	open;

	h_doc = 1;
	open = 1;
	while (cmdline && cmdline->type != NEWLINES && cmdline->type != PIPE)
	{
		if (cmdline->type == H_DOC)
			h_doc = ft_here_doc_write(cmdline->next->content);
		if (!h_doc)
			open = h_doc;
		cmdline = cmdline->next;
	}
	return (open);
}

int	ft_fill_files(t_cmdtable *table, t_cmdline *cmdline)
{
	t_cmdline	*line;
	int			open;

	line = cmdline;
	open = ft_here_doc(cmdline);
	while (open && line && line->type != NEWLINES && line->type != PIPE)
	{
		if (open && line->type == LESS)
			open = ft_infile_open(table, line);
		if (open && line->type == GREAT)
			open = ft_outfile_open(table, line, O_RDWR | O_CREAT | O_TRUNC);
		if (open && line->type == H_DOC)
			open = ft_here_doc_open(table, line);
		if (open && line->type == APPEND)
			open = ft_outfile_open(table, line, O_RDWR | O_CREAT | O_APPEND);
		line = line->next;
	}
	return (open);
}

void	make_cmdtable(t_data *data)
{
	t_cmdline	*line;
	t_cmdline	*temp;
	t_cmdtable	*cur_tab;

	line = data->cmd;
	while (line && line->type != NEWLINES)
	{
		ft_tableadd_back(&data->cmdtable, ft_tablenew());
		cur_tab = get_last(data->cmdtable);
		temp = line;
		cur_tab->status = ft_fill_files(cur_tab, line);
		ft_make_cmd_array(cur_tab, temp);
		while (line && line->type != PIPE)
			line = line->next;
		if (line)
			line = line->next;
	}
}

// void	make_cmdtable(t_data *data)
// {
// 	t_cmdline	*line;
// 	t_cmdline	*temp;
// 	t_cmdtable	*cur_tab;
// 	int			count;

// 	line = data->cmd;
// 	while (line && line->type != NEWLINES)
// 	{
// 		ft_tableadd_back(&data->cmdtable, new_table());
// 		cur_tab = get_last(data->cmdtable);
// 		temp = line;
// 		count = 0;
// 		while (line && line->type != PIPE)
// 		{
// 			if (is_redir(line->type))
// 				ft_fill_files_v2(cur_tab, &line);
// 			else if (line->type == WORD)
// 				count++;
// 			line = line->next;
// 		}
// 		ft_make_cmd_array(cur_tab, temp, count);
// 		if (line)
// 			line = line->next;
// 	}
// }

// void	ft_make_cmd_array(t_cmdtable *table, t_cmdline *cmdline, int count)
// {
// 	int	i;

// 	i = 0;
// 	table->cmd = malloc(sizeof(char *) * (count + 1));
// 	while (i < count)
// 	{
// 		if (is_redir(cmdline->type))
// 			cmdline = cmdline->next->next;
// 		else
// 		{
// 			table->cmd[i++] = ft_strdup(cmdline->content);
// 			cmdline = cmdline->next;
// 		}
// 	}
// 	table->cmd[i] = NULL;
// }

// void	ft_fill_files_v2(t_cmdtable *table, t_cmdline **line)
// {
// 	if ((*line)->type == LESS)
// 	{
// 		free(table->infile);
// 		table->infile = ft_strdup((*line)->next->content);
// 		table->infd = open((*line)->next->content, O_RDONLY);
// 		if (table->infd == -1)
// 			return (-1);
// 	}
// 	if ((*line)->type == GREAT)
// 	{
// 		free(table->outfile);
// 		table->outfile = ft_strdup((*line)->next->content);
// 		table->outfd = open((*line)->next->content, O_RDWR | O_CREAT | O_TRUNC,
// 				0644);
// 		if (table->outfd == -1)
// 			return (-1);
// 	}
// 	*line = (*line)->next;
// }
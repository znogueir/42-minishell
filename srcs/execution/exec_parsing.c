/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:50:19 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/19 01:09:48 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_count(t_cmdline *line)
{
	int	count;

	count = 0;
	while (line && line->content && line->type != NEWLINES \
	&& line->type != PIPE)
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
	if (count == 0)
	{
		table->cmd = NULL;
		return ;
	}
	table->cmd = malloc(sizeof(char *) * (count + 1));
	while (cmdline && i < count)
	{
		if (!cmdline->content)
			break ;
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
	int	count;

	h_doc = 1;
	open = 1;
	count = 0;
	while (cmdline && cmdline->type != NEWLINES && cmdline->type != PIPE)
	{
		if (cmdline->type == H_DOC)
			h_doc = ft_here_doc_write(cmdline->next->content, count++);
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
	int			i;
	int			count;

	count = 0;
	line = cmdline;
	open = ft_here_doc(cmdline);
	ft_fileadd_back(&table->infile, ft_filenew(0, ft_strdup(IN), LESS, -1));
	ft_fileadd_back(&table->outfile, ft_filenew(1, ft_strdup(OUT), GREAT, -1));
	i = 0;
	while (open && line && line->type != NEWLINES && line->type != PIPE)
	{
		if (open && line->type == LESS)
			open = ft_infile_open(table, line, i++);
		if (open && line->type == GREAT)
			open = ft_outfile_open(table, line, \
			O_RDWR | O_CREAT | O_TRUNC, i++);
		if (open && line->type == H_DOC)
			open = ft_here_doc_open(table, line, i++, count++);
		if (open && line->type == APPEND)
			open = ft_outfile_open(table, line, \
			O_RDWR | O_CREAT | O_APPEND, i++);
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
		// printf("cmdtable: %p\n", data->cmdtable);
		// printf("cmdtable->next: %p\n", data->cmdtable->next);
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

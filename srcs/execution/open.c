/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/02 19:20:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_infile_open(t_data *data, t_cmdtable *table, t_cmdline *line)
{
	int	fd;

	if (!line->next->content)
		return (data->order++,
			ft_putstr_fd("minishell: ambiguous redirect\n", 2), 0);
	if (is_directory(line->next->content))
		return (data->order++,
			ft_is_directory(line->next->content), 0);
	fd = open(line->next->content, O_RDONLY);
	ft_fileadd_back(&table->infile, \
	ft_filenew(data, fd, ft_strdup(data, line->next->content), LESS));
	if (fd == -1)
		return (data->order++, perror("minishell"), 0);
	return (data->order++, 1);
}

int	ft_outfile_open(t_data *data, t_cmdtable *table,
	t_cmdline *line, int settings)
{
	int	fd;

	if (is_directory(line->next->content))
		return (data->order++, ft_is_directory(line->next->content), 0);
	if (!line->next->content)
		return (data->order++,
			ft_putstr_fd("minishell: ambiguous redirect\n", 2), 0);
	if (line && line->next && line->next->content)
	{
		fd = open(line->next->content, settings, 0644);
		ft_fileadd_back(&table->outfile, \
		ft_filenew(data, fd, ft_strdup(data, line->next->content), line->type));
		if (fd == -1)
			return (data->order++, 0);
	}
	else
		return (data->order++, 0);
	return (1);
}

int	ft_open_loop(t_data *data, t_cmdtable *table, t_cmdline *line)
{
	int	open;

	data->order = 0;
	open = 1;
	while (open && line && line->type != PIPE)
	{
		while (line && !line->content)
			line = line->next;
		if (!line)
			break ;
		if (open && line->type == LESS)
			open = ft_infile_open(data, table, line);
		if (open && line->type == GREAT)
			open = ft_outfile_open(data, table, line, \
			O_RDWR | O_CREAT | O_TRUNC);
		if (open && line->type == H_DOC)
			open = ft_here_doc_open(data, table, line, data->hdoc_open++);
		if (open && line->type == APPEND)
			open = ft_outfile_open(data, table, line, \
			O_RDWR | O_CREAT | O_APPEND);
		line = line->next;
	}
	return (open);
}

int	ft_fill_files(t_data *data, t_cmdtable *table, t_cmdline *cmdline)
{
	t_cmdline	*line;
	int			open;

	line = cmdline;
	data->order = -1;
	ft_fileadd_back(&table->infile,
		ft_filenew(data, 0, ft_strdup(data, IN), LESS));
	ft_fileadd_back(&table->outfile,
		ft_filenew(data, 1, ft_strdup(data, OUT), GREAT));
	open = ft_open_loop(data, table, line);
	if (open == 0)
		g_exit = 1;
	return (open);
}

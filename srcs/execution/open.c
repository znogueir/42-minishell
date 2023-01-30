/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/30 17:39:57 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_infile_open(t_cmdtable *table, t_cmdline *line, int order)
{
	int	fd;

	if (!line->next->content)
		return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), 0);
	if (is_directory(line->next->content))
		return (ft_is_directory(line->next->content), 0);
	fd = open(line->next->content, O_RDONLY);
	ft_fileadd_back(&table->infile, \
	ft_filenew(NULL, fd, ft_strdup(line->next->content), LESS, order));
	//add data to ft_filenew
	if (fd == -1)
		return (perror("minishell"), 0);
	return (1);
}

int	ft_outfile_open(t_cmdtable *table, t_cmdline *line, int settings, int order)
{
	int	fd;

	if (is_directory(line->next->content))
		return (ft_is_directory(line->next->content), 0);
	if (!line->next->content)
		return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), 0);
	if (line && line->next && line->next->content)
	{
		fd = open(line->next->content, settings, 0644);
		ft_fileadd_back(&table->outfile, \
		ft_filenew(NULL, fd, ft_strdup(line->next->content), line->type, order));
		//add data to ft_filenew
		if (fd == -1)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	ft_open_loop(t_data *data, t_cmdtable *table, t_cmdline *line)
{
	int	open;
	int	i;

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
	return (open);
}

int	ft_fill_files(t_data *data, t_cmdtable *table, t_cmdline *cmdline)
{
	t_cmdline	*line;
	int			open;

	line = cmdline;
	ft_fileadd_back(&table->infile, ft_filenew(data, 0, ft_strdup(IN), LESS, -1));
	ft_fileadd_back(&table->outfile, ft_filenew(data, 1, ft_strdup(OUT), GREAT, -1));
	open = ft_open_loop(data, table, line);
	if (open == 0)
		g_exit = 1;
	return (open);
}

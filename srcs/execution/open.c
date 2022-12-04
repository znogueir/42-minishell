/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/04 23:27:07 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_error_opening(t_cmdtable *table, char *filename)
// {
// 	perror(filename);
// 	while (table)
// 	{
// 		if (table->infd > 2)
// 			close(table->infd);
// 		if (table->outfd > 2)
// 			close(table->outfd);
// 		table = table->next;
// 	}
// }

// void	close_files(t_cmdtable *table)
// {
// 	t_cmdtable	*beg;

// 	beg = table;
// 	while (table)
// 	{
// 		if (table->infd < 0)
// 			return (ft_error_opening(beg, table->infile));
// 		else if (table->outfd < 0)
// 			return (ft_error_opening(beg, table->outfile));
// 		else
// 			table = table->next;
// 	}
// }

int	ft_here_doc_write(char *limiter)
{
	char	*str;
	int		fd;
	char	*limit;

	limit = ft_strjoin(ft_strdup(limiter), "\n");
	fd = open(".temp_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
	{
		free(limit);
		return (fd);
	}
	str = NULL;
	while (!str || ft_strncmp(limit, str, ft_strlen(limit)))
	{
		write(1, "heredoc> ", 9);
		free(str);
		str = get_next_line(0);
		if (ft_strncmp(limit, str, ft_strlen(limit)))
			write(fd, str, ft_strlen(str));
	}
	free(str);
	close(fd);
	free(limit);
	return (1);
}

int	ft_infile_open(t_cmdtable *table, t_cmdline *line, int order)
{
	int	fd;

	fd = open(line->next->content, O_RDONLY);
	ft_fileadd_back(&table->infile, \
	ft_filenew(fd, ft_strdup(line->next->content), LESS, order));
	if (fd == -1)
		return (0);
	return (1);
}

int	ft_outfile_open(t_cmdtable *table, t_cmdline *line, int settings, int order)
{
	int	fd;

	fd = open(line->next->content, settings, 0644);
	ft_fileadd_back(&table->outfile, \
	ft_filenew(fd, ft_strdup(line->next->content), line->type, order));
	if (fd == -1)
		return (0);
	return (1);
}

int	ft_here_doc_open(t_cmdtable *table, t_cmdline *line, int order)
{
	int	fd;

	fd = open(".temp_heredoc", O_RDONLY);
	ft_fileadd_back(&table->infile, \
	ft_filenew(fd, ft_strdup(line->next->content), H_DOC, order));
	if (fd == -1)
		return (0);
	return (1);
}

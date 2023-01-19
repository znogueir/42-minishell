/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/19 21:33:20 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc_write(t_data *data, char *limiter, int count)
{
	char	*str;
	int		fd;
	char	*limit;
	char	*temp;
	char	*filename;

	(void)data;
	temp = ft_itoa(count);
	filename = ft_strjoin(ft_strdup(".temp_heredoc_"), temp);
	limit = ft_strjoin(ft_strdup(limiter), "\n");
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(temp);
	if (!fd)
	{
		free(limit);
		free(filename);
		return (fd);
	}
	signal(SIGINT, handle_sig_heredocs);
	while (1)
	{
		// ft_putstr_fd("heredoc> ", 1);
		// str = get_next_line(0);
		str = readline("heredoc> ");
		// printf("str : %s\n", str);
		if (g_exit == 257)
		{
			g_exit = 130;
			free(str);
			close(fd);
			free(limit);
			free(filename);
			// unlink(filename);
			dup2(data->insave, 0);
			close(data->insave);
			// signal(SIGINT, SIG_DFL);
			return (signal(SIGINT, handle_sigint), 0);
		}
		if (!str || !ft_strcmp(limiter, str))
			break ;
		write(fd, str, ft_strlen(str));
		ft_putstr_fd("\n", fd);
		free(str);
	}
	if (!str)
	{
		ft_putstr_fd("minishell: warning: here-document \
delimited by end-of-file (wanted \'", 2);
		ft_putstr_fd(limiter, 2);
		ft_putstr_fd("\')\n", 2);
	}
	free(str);
	free(filename);
	close(fd);
	free(limit);
	// signal(SIGINT, SIG_DFL);
	return (signal(SIGINT, handle_sigint), 1);
}

int	ft_infile_open(t_cmdtable *table, t_cmdline *line, int order)
{
	int	fd;

	if (!line->next->content)
		return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), 0);
	if (is_directory(line->next->content))
		return (ft_is_directory(line->next->content), 0);
	fd = open(line->next->content, O_RDONLY);
	ft_fileadd_back(&table->infile, \
	ft_filenew(fd, ft_strdup(line->next->content), LESS, order));
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
		ft_filenew(fd, ft_strdup(line->next->content), line->type, order));
		if (fd == -1)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	ft_here_doc_open(t_cmdtable *table, t_cmdline *line, int order, int count)
{
	int		fd;
	char	*tmp;
	char	*filename;

	(void)line;
	tmp = ft_itoa(count);
	filename = ft_strjoin(ft_strdup(".temp_heredoc_"), tmp);
	fd = open(filename, O_RDONLY);
	free(tmp);
	ft_fileadd_back(&table->infile, \
	ft_filenew(fd, filename, H_DOC, order));
	if (fd == -1)
		return (0);
	return (1);
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

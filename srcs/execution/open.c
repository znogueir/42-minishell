/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/22 00:40:42 by yridgway         ###   ########.fr       */
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
	free(filename);
	if (!fd)
	{
		free(limit);
		return (fd);
	}
	str = NULL;
	while (!str || ft_strncmp(limit, str, ft_strlen(limit)))
	{
		signal(SIGINT, handle_sig_heredocs);
		signal(SIGQUIT, handle_sig_heredocs);
		write(1, "heredoc> ", 9);
		free(str);
		signal(SIGINT, SIG_IGN);
		str = get_next_line(0);
		// if (!str)
		// 	break ;
		ft_printf("[[%d]]\n", g_exit);
		ft_printf("[%s]", str);
		if (ft_strncmp(limit, str, ft_strlen(limit)))
		{
			write(fd, str, ft_strlen(str));
		}
		if (g_exit == 257)
		{
			// heredoc_rm(exec->tok_lst);
			// dup2(data->insave, 0);
			// close(data->insave);
			ft_putstr_fd("g_exit257\n", 2);
			g_exit = 130;
			free(str);
			str = ft_strdup("urmom");
			free(str);
			close(fd);
			free(limit);
			return (0);
			// break ;
			// return (1);
		}
	}
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	if (!str)
	{
		ft_putstr_fd("\nminishell: warning: here-document delimited by end-of-file (wanted \'", 2);
		ft_putstr_fd(limiter, 2);
		ft_putstr_fd("\')\n", 2);
	}
	free(str);
	close(fd);
	free(limit);
	return (1);
}

int	ft_infile_open(t_cmdtable *table, t_cmdline *line, int order)
{
	int	fd;

	if (is_directory(line->next->content))
	{
		ft_is_directory(line->next->content);
		g_exit = 1;
		return (0);
	}
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

	// if (is_directory(line->next->content))
	// {
	// 	ft_is_directory(line->next->content);
	// 	g_exit = 1;
	// 	return (0);
	// }
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

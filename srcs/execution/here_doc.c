/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/06 20:21:25 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_loop(t_data *data, int fd, char **str, char *limiter)
{
	int	insave;

	insave = dup(0);
	(void)data;
	while (1)
	{
		*str = readline("heredoc> ");
		ft_add_to_mem(data, *str);
		if (g_exit == 257)
		{
			g_exit = 130;
			ft_free(*str);
			ft_close(&fd);
			dup2(insave, 0);
			ft_close(&insave);
			return (0);
		}
		if (!*str || !ft_strcmp(limiter, *str))
			break ;
		write(fd, *str, ft_strlen(*str));
		ft_putstr_fd("\n", fd);
		ft_free(*str);
	}
	ft_close(&insave);
	return (1);
}

void	here_doc_error(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document \
delimited by end-of-file (wanted \'", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("\')\n", 2);
}

int	ft_here_doc_write(t_data *data, char *limiter, int count)
{
	char	*str;
	int		fd;
	char	*temp;
	char	*filename;

	(void)data;
	temp = ft_itoa(data, count);
	filename = ft_strjoin(data, ft_strdup(data, "/tmp/.temp_heredoc_"), temp);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_free(filename);
	ft_free(temp);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: problem opening heredoc\n", 2);
		return (fd);
	}	
	signal(SIGINT, handle_sig_heredocs);
	if (!here_doc_loop(data, fd, &str, limiter))
		return (0);
	if (!str)
		here_doc_error(limiter);
	ft_free(str);
	ft_close(&fd);
	return (1);
}

int	ft_here_doc_open(t_data *data,
	t_cmdtable *table, t_cmdline *line, int count)
{
	int		fd;
	char	*tmp;
	char	*filename;

	(void)line;
	tmp = ft_itoa(data, count);
	filename = ft_strjoin(data, ft_strdup(data, "/tmp/.temp_heredoc_"), tmp);
	fd = open(filename, O_RDONLY);
	ft_free(tmp);
	ft_fileadd_back(&table->infile, \
	ft_filenew(data, fd, filename, H_DOC));
	if (fd == -1)
		return (0);
	return (1);
}

int	ft_here_doc(t_data *data, t_cmdline *cmdline)
{
	int	h_doc;

	h_doc = 1;
	while (h_doc > 0 && cmdline)
	{
		if (cmdline->type == H_DOC)
			h_doc = \
			ft_here_doc_write(data, cmdline->next->content, data->hdoc_write++);
		cmdline = cmdline->next;
	}
	return (h_doc);
}

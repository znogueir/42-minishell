/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/19 22:31:46 by ionorb           ###   ########.fr       */
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

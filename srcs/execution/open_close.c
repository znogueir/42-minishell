/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2022/11/30 16:53:02 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	ft_error_opening(t_filelist **filelist, char *filename)
{
	perror(filename);
	while (*filelist)
	{
		if ((*filelist)->fd != -1)
			close((*filelist)->fd);
		*filelist = (*filelist)->next;
	}
}

void	open_redir_files(t_data *data, t_cmdtable *table)
{
	t_filelist *filelist;

	while (table)
	{
		if (table->type == GREAT)
			ft_fileadd_back(&data->filelist,
				ft_filenew(open(table->operator + 1, O_RDWR | O_CREAT | O_TRUNC, 0644),
					ft_strdup(table->operator + 1)));
		else if (table->type == LESS)
			ft_fileadd_back(&data->filelist, ft_filenew(open(table->operator + 1, O_RDONLY),
				ft_strdup(table->operator + 1)));
		table = table->next;
	}
	filelist = data->filelist;
	while (filelist)
	{
		if (filelist->fd < 0)
			ft_error_opening(&filelist, filelist->filename);
		else
			filelist = filelist->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:13:40 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 20:38:24 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdline	*ft_cmdnew(t_data *data, void *content)
{
	t_cmdline	*cell;

	cell = ft_malloc(NULL, data, sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->content = content;
	cell->type = find_token_type(content);
	cell->next = NULL;
	return (cell);
}

t_env	*ft_envnew(t_data *data, char *name, char *content, int is_env)
{
	t_env	*cell;

	cell = ft_malloc(NULL, data, sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->env = is_env;
	cell->name = name;
	cell->content = content;
	cell->next = NULL;
	return (cell);
}

t_cmdtable	*ft_tablenew(t_data *data)
{
	t_cmdtable	*cell;

	cell = ft_malloc(NULL, data, sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->infile = NULL;
	cell->outfile = NULL;
	cell->cmd = NULL;
	cell->pid = -1;
	cell->next = NULL;
	cell->status = 1;
	return (cell);
}

t_filelist	*ft_filenew(t_data *data, int fd, char *filename, int type, int order)
{
	t_filelist	*cell;

	cell = ft_malloc(NULL, data, sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->fd = fd;
	cell->filename = filename;
	cell->type = type;
	cell->order = order;
	cell->next = NULL;
	return (cell);
}

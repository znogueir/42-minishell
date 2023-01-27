/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:33:03 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/27 15:05:13 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdline	*get_last_cmd(t_cmdline *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}

t_cmdtable	*get_last(t_cmdtable *table)
{
	while (table->next)
	{
		table = table->next;
	}
	return (table);
}

t_filelist	*file_get_last(t_filelist *filelist)
{
	t_filelist	*file;

	file = filelist;
	while (file && file->next)
	{
		file = file->next;
	}
	return (file);
}

t_cmdline	*ft_cmdpop(t_cmdline **cmdline, t_cmdline *topop)
{
	t_cmdline	*lst;
	t_cmdline	*save;

	lst = *cmdline;
	save = topop;
	while (lst->next && lst->next != topop)
		lst = lst->next;
	if (lst == topop)
	{
		return (NULL);
	}
	if (lst->next == topop)
	{
		save = lst->next->next;
		lst->next = save;
		free(topop->content);
		free(topop);
	}
	return (save);
}

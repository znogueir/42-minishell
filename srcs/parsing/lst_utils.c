/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:33:03 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/22 20:33:04 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		// free(topop->content);
		// free(topop);
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

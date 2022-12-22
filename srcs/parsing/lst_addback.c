/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:29:38 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/17 14:30:24 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*p;

	if (lst && *lst)
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
	else if (lst)
		*lst = new;
}

void	ft_cmdadd_back(t_cmdline **lst, t_cmdline *new)
{
	t_cmdline	*p;

	if (lst && *lst)
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
	else if (lst)
		*lst = new;
}

void	ft_tableadd_back(t_cmdtable **lst, t_cmdtable *new)
{
	t_cmdtable	*p;

	if (lst && *lst)
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
	else if (lst)
		*lst = new;
}

void	ft_fileadd_back(t_filelist **lst, t_filelist *new)
{
	t_filelist	*p;

	if (lst && *lst)
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
	else if (lst)
		*lst = new;
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

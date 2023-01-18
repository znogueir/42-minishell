/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:29:38 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/18 15:33:02 by yridgway         ###   ########.fr       */
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

// void	ft_pidadd_back(t_process **lst, int pid)
// {
// 	t_process	*p;
// 	t_process	*new;
//
// 	new = ft_mallocator(NULL, data, sizeof(*new));
// 	if (!new)
// 		return ;
// 	new->pid = pid;
// 	new->next = NULL;
// 	if (lst && *lst)
// 	{
// 		p = *lst;
// 		while (p->next)
// 			p = p->next;
// 		p->next = new;
// 	}
// 	else if (lst)
// 		*lst = new;
// }

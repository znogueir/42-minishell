/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:29:38 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_cmdline *cmd)
{
	if (cmd)
		ft_printf("\n");
	while (cmd)
	{
		ft_printf("\t{%s%s%s}", ORANGE, cmd->content, RES_COL);
		ft_printf(" - type : %s\n" RES_COL, convert_type(cmd->type));
		cmd = cmd->next;
	}
	if (cmd)
		ft_printf("\n");
}

t_cmdline	*ft_cmdnew(void *content)
{
	t_cmdline	*cell;

	cell = malloc(sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->content = content;
	cell->type = find_token_type(content);
	cell->next = NULL;
	return (cell);
}

t_env	*ft_envnew(char *name, char *content)
{
	t_env	*cell;

	cell = malloc(sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->name = name;
	cell->content = content;
	cell->next = NULL;
	return (cell);
}

t_cmdtable	*ft_tablenew(void)
{
	t_cmdtable	*cell;

	cell = malloc(sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->infile = NULL;
	cell->outfile = NULL;
	cell->cmd = NULL;
	cell->next = NULL;
	return (cell);
}

t_filelist	*ft_filenew(int fd, char *filename, int type, int order)
{
	t_filelist	*cell;

	cell = malloc(sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->fd = fd;
	cell->filename = filename;
	cell->type = type;
	cell->order = order;
	cell->next = NULL;
	return (cell);
}

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

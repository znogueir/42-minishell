/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:29:38 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/13 14:29:40 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_cmdline *cmd)
{
	while (cmd)
	{
		ft_printf("{%s%s%s}", ORANGE, cmd->content, RES_COL);
		ft_printf(" - type : %s\n"RES_COL, convert_type(cmd->type));
		cmd = cmd->next;
	}
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

t_cmdtable	*ft_tablenew(char **cmd, char *operator, int type)
{
	t_cmdtable	*cell;

	cell = malloc(sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->cmd = cmd;
	cell->operator = operator;
	cell->type = type;
	cell->next = NULL;
	return (cell);
}

t_filelist	*ft_filenew(int	fd, char *filename)
{
	t_filelist	*cell;

	cell = malloc(sizeof(*cell));
	if (!cell)
		return (NULL);
	cell->fd = fd;
	cell->filename = filename;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:34:04 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/06 01:52:07 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_liberate(t_data *data, t_mem *mem, int type)
{
	t_mem	*prev;

	if (data)
	{
		ft_close_fds(data, NULL, NULL);
		free_table(data, data->cmdtable);
		ft_close(&data->insave);
		ft_close(&data->outsave);
		ft_free(data->line);
	}
	while (mem)
	{
		if (mem->ptr)
		{
			free(mem->ptr);
			mem->ptr = NULL;
		}
		prev = mem;
		mem = mem->next;
		free(prev);
	}
	if (type == EXIT_FREE)
		exit(g_exit);
	return (NULL);
}

t_mem	*mem_addback(t_data *data, t_mem **mem, t_mem *new)
{
	t_mem	*tmp;

	tmp = *mem;
	if (!new)
		return (ft_liberate(data, *mem, -777), NULL);
	if (!tmp)
		return (mem = &new, *mem);
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*mem);
}

t_mem	*mem_new(size_t size, void *thing)
{
	t_mem	*new;
	char	*err;

	err = "Error: malloc failed\n";
	new = break_malloc(sizeof(t_mem));//malloc(sizeof(t_mem));
	if (!new)
		return (ft_putstr_fd(err, 2), g_exit = 254, NULL);
	if (thing)
		new->ptr = thing;
	else
		new->ptr = break_malloc(size);//malloc(size);
	if (!new->ptr)
	{
		ft_putstr_fd(err, 2);
		g_exit = 254;
		free(new);
		new = NULL;
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	*ft_malloc(void *free, t_data *data, long long int size)
{
	static t_mem	*mem = NULL;
	t_mem			*new;

	if (free && size == ADD_TO_MEM)
		return (mem = mem_addback(data, &mem, mem_new(0, free)));
	if (free)
		return (ft_free_one(mem, free), NULL);
	if (size == EXIT_FREE)
		return (mem = ft_liberate(data, mem, size), NULL);
	if (size == FREE_ALL)
		return (mem_clean(data, mem), NULL);
	new = mem_new(size, NULL);
	if (!new)
		ft_liberate(data, mem, -777);
	mem = mem_addback(data, &mem, new);
	return (new->ptr);
}

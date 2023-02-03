/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:34:04 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/03 20:27:19 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_one(t_mem *mem, void *thing)
{
	while (mem)
	{
		if (mem->ptr == thing)
		{
			free(mem->ptr);
			mem->ptr = NULL;
			return ;
		}
		mem = mem->next;
	}
}

void	mem_clean(t_data *data, t_mem *mem)
{
	t_mem	*prev;
	t_mem	*after;

	free_cmd(data->cmd);
	data->cmd = NULL;
	ft_free(data->line);
	data->line = NULL;
	prev = mem;
	mem = mem->next;
	after = mem->next;
	while (mem && mem->next)
	{
		if (!mem->ptr)
		{
			free(mem);
			mem = after;
			prev->next = after;
		}
		prev = mem;
		mem = mem->next;
		after = mem->next;
	}
}

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

t_mem	*mem_addback(t_mem **mem, t_mem *new)
{
	t_mem	*tmp;

	tmp = *mem;
	if (!tmp)
		return (mem = &new, *mem);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*mem);
}

t_mem	*mem_new(size_t size, void *thing)
{
	t_mem	*new;
	char	*err;

	err = "Error: malloc failed\n";
	new = malloc(sizeof(t_mem));
	if (!new)
		return (NULL);
	if (thing)
		new->ptr = thing;
	else
		new->ptr = malloc(size);//break_malloc(size);
	if (!new->ptr)
	{
		ft_putstr_fd(err, 2);
		g_exit = 256;
		free(new);
		new = NULL;
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

// void	ft_print_mem(t_mem *mem)
// {
// 	int	i = 0;
// 	while (mem)
// 	{
// 		i++;
// 		mem = mem->next;
// 	}
// 	printf("%d\n", i);
// }

t_mem	*ft_add_mem(void *thing, t_mem *mem)
{
	t_mem	*new;

	new = mem_new(0, thing);
	return (mem_addback(&mem, new));
}

void	*ft_malloc(void *free, t_data *data, long long int size)
{
	static t_mem	*mem = NULL;
	t_mem			*new;

	if (free && size == ADD_TO_MEM)
		return (mem = ft_add_mem(free, mem), NULL);
	if (free)
		return (ft_free_one(mem, free), NULL);
	if (size == EXIT_FREE)
		return (mem = ft_liberate(data, mem, size), NULL);
	if (size == FREE_ALL)
		return (mem_clean(data, mem), NULL);
	new = mem_new(size, NULL);
	if (!new)
		ft_liberate(data, mem, size);
	mem = mem_addback(&mem, new);
	return (new->ptr);
}

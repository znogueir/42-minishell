/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:34:04 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/01 20:40:47 by yridgway         ###   ########.fr       */
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
	ft_putstr_fd("not freeing\n", 2);
}

void	ft_liberate(t_data *data, t_mem *mem, int type)
{
	t_mem	*prev;

	if (data)
	{
		ft_close_fds(data, NULL, NULL);
		free_table(data, data->cmdtable);
		if (data->insave && data->insave != 0 && data->insave != -1)
			close(data->insave);
		if (data->outsave && data->outsave != 1 && data->outsave != -1)
			close(data->outsave);
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
	printf("end\n");
	if (type == EXIT_FREE)
		exit(g_exit);
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

t_mem	*mem_new(size_t size)
{
	t_mem	*new;
	char	*err;

	err = "Error: malloc failed\n";
	new = malloc(sizeof(t_mem));
	if (!new)
		return (NULL);
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

void	*ft_malloc(void *free, t_data *data, long long int size)
{
	static t_mem	*mem = NULL;
	t_mem			*new;

	if (free)
		return (ft_free_one(mem, free), NULL);
	if (size == EXIT_FREE || size == FREE_ALL)
		ft_liberate(data, mem, size);
	new = mem_new(size);
	if (!new)
		ft_liberate(data, mem, size);
	mem = mem_addback(&mem, new);
	return (new->ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:34:04 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/30 18:42:16 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_liberate(t_data *data, t_mem *mem)
{
	t_mem	*prev;

	ft_close_fds(data, NULL, NULL);
	close(data->insave);
	close(data->outsave);
	while (mem)
	{
		printf("free\n");
		prev = mem;
		mem = mem->next;
		free(prev->ptr);
		free(prev);
	}
	free(data);
	ft_putstr_fd("Error: malloc failed\n", 2);
	exit(1);
}

t_mem	*mem_addback(t_mem **mem, t_mem *new)
{
	t_mem	*tmp;

	tmp = *mem;
	if (!tmp)
	{
		printf("first\n");
		mem = &new;
		return (*mem);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*mem);
}

t_mem	*mem_new(size_t size)
{
	t_mem	*new;

	new = malloc(sizeof(t_mem));
	if (!new)
		return (NULL);
	new->ptr = malloc(size);
	if (!new->ptr)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

void	*ft_malloc(t_data *data, long long int size)
{
	static t_mem	*mem = NULL;
	t_mem			*new;

	if (size == -777)
		ft_liberate(data, mem);
	new = mem_new(size);
	if (!new)
		ft_liberate(data, mem);
	mem = mem_addback(&mem, new);
	return (new->ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:34:04 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/30 22:53:01 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_liberate(t_data *data, t_mem *mem)
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
		// printf("free\n");
		prev = mem;
		mem = mem->next;
		free(prev->ptr);
		free(prev);
	}
	// free(data);
	printf("end\n");
	exit(g_exit);
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
	char	*err;

	err = "Error: malloc failed\n";
	new = malloc(sizeof(t_mem));
	if (!new)
		return (NULL);
	new->ptr = break_malloc(size);
	if (!new->ptr)
	{
		ft_putstr_fd(err, 2);
		g_exit = 256;
		return (free(new), NULL);
	}
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

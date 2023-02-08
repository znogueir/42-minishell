/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:36:18 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/06 01:52:44 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_print_mem(t_mem *mem)
// {
// 	int	i = 0;

// 	while (mem)
// 	{
// 		i++;
// 		printf("mem: %p\n", mem->ptr);
// 		mem = mem->next;
// 	}
// 	printf("%d\n", i);
// }

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
	if (mem)
		mem = mem->next;
	while (mem && mem->next)
	{
		after = mem->next;
		if (!mem->ptr)
		{
			free(mem);
			mem = after;
			prev->next = after;
		}
		prev = mem;
		mem = mem->next;
	}
}

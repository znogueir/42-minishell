/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:25:40 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/03 20:24:32 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *ptr)
{
	ft_malloc(ptr, 0, 0);
}

void	ft_quit(t_data *data)
{
	int	i;

	i = 0;
	while (!unlink(ft_strjoin(data, "/tmp/.temp_heredoc_", ft_itoa(data, i))))
		i++;
	ft_malloc(NULL, data, EXIT_FREE);
}

void	clean_memory(t_data *data)
{
	int	i;

	i = 0;
	while (!unlink(ft_strjoin(data, "/tmp/.temp_heredoc_", ft_itoa(data, i))))
		i++;
	ft_malloc(NULL, data, FREE_ALL);
}

void	ft_add_to_mem(t_data *data, void *thing)
{
	ft_malloc(thing, data, ADD_TO_MEM);
}

void	ft_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -2;
	}
}

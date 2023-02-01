/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:25:40 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 23:42:18 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *ptr)
{
	ft_malloc(ptr, 0, 0);
}

void	ft_quit(t_data *data)
{
	ft_malloc(NULL, data, EXIT_FREE);
}

void	free_all(t_data *data)
{
	ft_malloc(NULL, data, FREE_ALL);
}

void	ft_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -2;
	}
}

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

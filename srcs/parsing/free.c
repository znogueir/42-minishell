/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:25:40 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/16 18:56:20 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		// printf("tab: %s\n", tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(t_data *data)
{
	ft_free(data->line);
	free_cmd(data->cmd);
	ft_free(data->wc);
	free_split(data->char_env);
	free_env(data->loc_env);
	free_split(data->paths);
	if (data->cmdtable)
		free_table(data, data->cmdtable);
	ft_free(data);
}

void	ft_exit_fork(t_data *data, char **command, int ext)
{
	ft_close_fds(data);
	close(data->insave);
	close(data->outsave);
	free_table(data, data->cmdtable);
	free_all(data);
	free_split(command);
	exit(ext);
}

void	*break_malloc(int size)
{
	//cur_breakpoint++;
	//printf("breakpoint: %d\n", cur_breakpoint);
	if (break_malloc_at == cur_breakpoint)
		return (ft_putstr_fd("mallocd ur mom\n", 2), NULL);
	return (malloc(size));
}

void	*ft_mallocator(t_data *data, int size)
{
	void	*thing;

	thing = break_malloc(size);
	if (!thing)
	{
		free_all(data);
		exit(258);
	}
	return (thing);
}
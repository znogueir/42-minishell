/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:25:40 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 20:23:56 by yridgway         ###   ########.fr       */
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
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

// void	free_all(t_data *data)
// {
// 	// ft_ft_free(data->line);
// 	// free_cmd(data->cmd);
// 	// ft_ft_free(data->wc);
// 	free_split(data->char_env);
// 	// free_env(data->loc_env);
// 	free_split(data->paths);
// 	if (data->cmdtable)
// 		free_table(data, data->cmdtable);
// 	// ft_ft_free(data);
// }

// void	ft_exit_fork(t_data *data, char **command, int ext)
// {
// 	ft_close_fds(data, NULL, NULL);
// 	close(data->insave);
// 	close(data->outsave);
// 	free_table(data, data->cmdtable);
// 	free_all(data);
// 	free_split(command);
// 	exit(ext);
// }

// void	ft_malloc_exit(void *extra, t_data *data)
// {
// 	// ft_putstr_fd("\nmallocd ur mom\n\n", 2);
// 	// ft_free(extra);
// 	// free_all(data);
// 	exit(258);
// }

// void	*ft_mallocator(void	*extra, t_data *data, int size)
// {
// 	void	*thing;

// 	thing = break_malloc(size);
// 	if (!thing)
// 		ft_malloc_exit(extra, data);
// 	return (thing);
// }

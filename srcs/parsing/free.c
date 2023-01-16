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
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(t_data *data)
{
	free(data->line);
	free_cmd(data->cmd);
	//if (data->char_env)
	free(data->wc);
	free_split(data->char_env);
	free_env(data->loc_env);
	free_split(data->paths);
	// free_process(data->process);
	//free_table(data->cmdtable);
	free(data);
}

void	ft_exit_fork(t_data *data, char **command, int ext)
{
	ft_close_fds(data);
	close(data->insave);
	close(data->outsave);
	free_table(data, data->cmdtable);
	// if ((char *)data->line != NULL)
	free_all(data);
	free_split(command);
	exit(ext);
}

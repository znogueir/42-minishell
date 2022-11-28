/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:25:40 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/23 19:26:24 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	reset_cmd(t_data *data)
{
	free_cmd(data->cmd);
	data->cmd = NULL;
}

void	free_cmd(t_cmdline *cmd)
{
	t_cmdline	*prev;

	while (cmd)
	{
		prev = cmd;
		cmd = cmd->next;
		free(prev->content);
		free(prev);
	}
}

void	free_env(t_env *loc_env)
{
	t_env	*prev;

	while (loc_env)
	{
		prev = loc_env;
		loc_env = loc_env->next;
		free(prev->name);
		free(prev->content);
		free(prev);
	}
}

void	free_all(t_data *data)
{
	free(data->line);
	free_cmd(data->cmd);
	free_env(data->loc_env);
	free(data);
}

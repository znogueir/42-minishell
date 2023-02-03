/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:30 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/02 18:56:00 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_identifier(char *cmd)
{
	if (cmd && cmd[0] && cmd[1] && cmd[0] == '-')
	{
		g_exit = 2;
		return (ft_putstr_fd("minishell: unset: invalid option\n", 2), 1);
	}
	return (0);
}

int	ft_unset(t_data *data, char **cmd)
{
	t_env	*cur;
	t_env	*prev;
	int		i;

	i = 0;
	prev = NULL;
	if (check_unset_identifier(cmd[1]))
		return (2);
	while (cmd[++i] && data->loc_env)
	{
		cur = data->loc_env;
		while (cur && better_strncmp(cur->name, cmd[i], ft_strlen(cmd[i])))
		{
			prev = cur;
			cur = cur->next;
		}
		if (!prev)
			data->loc_env = data->loc_env->next;
		else
			prev->next = cur->next;
		ft_free(cur->name);
		ft_free(cur->content);
		ft_free(cur);
	}
	return (0);
}

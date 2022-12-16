/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:30 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, char **cmd)
{
	t_env	*cur;
	t_env	*prev;
	int		i;

	i = 1;
	while (cmd[i])
	{
		cur = data->loc_env;
		while (cur && better_strncmp(cur->name, cmd[i], ft_strlen(cmd[i])))
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur)
		{
			prev->next = cur->next;
			free(cur->name);
			free(cur->content);
			free(cur);
		}
		i++;
	}
	return (0);
}

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

int	check_unset_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (!((cmd[0] >= 'a' && cmd[0] <= 'z') || \
	(cmd[0] >= 'A' && cmd[0] <= 'Z') || cmd[0] == '_'))
	{
		g_exit = 1;
		return (write(2, "minishell: export: invalid identifier\n", 39), 1);
	}
	while (cmd[i])
	{
		if (!(is_alphanum(cmd[i]) || cmd[i] == '_'))
		{
			g_exit = 1;
			return (write(2, "minishell: export: invalid identifier\n", 39), 1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_data *data, char **cmd)
{
	t_env	*cur;
	t_env	*prev;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (check_unset_identifier(cmd[i]))
			continue ;
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
	}
	return (0);
}

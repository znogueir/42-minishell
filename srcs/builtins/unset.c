/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:30 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/15 17:23:31 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_data *data, char *name)
{
	t_env	*cur;
	t_env	*prev;

	cur = data->loc_env;
	ft_printf("test cmd : unset $%s\n", name);
	while (cur && better_strncmp(cur->name, name, ft_strlen(name)))
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
	return (0);
}

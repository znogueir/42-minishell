/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:15 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/15 17:23:17 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_data *data, char *name, char *content, int append)
{
	t_env	*p_env;

	p_env = data->loc_env;
	while (p_env && better_strncmp(p_env->name, name, ft_strlen(name)))
		p_env = p_env->next;
	if (p_env)
	{
		free(name);
		if (append)
		{
			p_env->content = ft_strjoin(p_env->content, content);
			//protect malloc -> return 1;
			free(content);
			return (0);
		}
		free(p_env->content);
		p_env->content = content;
		return (0);
	}
	ft_envadd_back(&(data->loc_env), ft_envnew(name, content));
	return (0);
}

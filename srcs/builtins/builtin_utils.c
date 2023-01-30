/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:42:44 by ionorb            #+#    #+#             */
/*   Updated: 2023/01/30 21:39:12 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char *name, char *content)
{
	if (!content)
		printf("export %s\n", name);
	else
		printf("export %s=\"%s\"\n", name, content);
}

int	get_env_len(t_env **p_env, t_env **env_min)
{	
	int	env_len;

	env_len = 0;
	while (*p_env)
	{
		if (ft_strcmp((*env_min)->name, (*p_env)->name) > 0)
			*env_min = *p_env;
		*p_env = (*p_env)->next;
		env_len++;
	}
	print_export((*env_min)->name, (*env_min)->content);
	return (env_len);
}

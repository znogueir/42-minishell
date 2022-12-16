/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:22:57 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *loc_env)
{
	t_env	*print_env;

	print_env = loc_env;
	while (print_env)
	{
		ft_printf("%s=%s\n", print_env->name, print_env->content);
		print_env = print_env->next;
	}
	return (0);
}

void	split_env(char **name, char **content, char **env)
{
	static int	i = 0;
	int			j;

	j = 0;
	while (env[i][j] != '=')
		j++;
	*name = ft_substr(env[i], 0, j);
	*content = ft_substr(env[i], j + 1, ft_strlen(env[i] + j + 1));
	i++;
}

void	set_env(char **env, t_data *data)
{
	int		i;
	char	*name;
	char	*content;
	char	*tmp;

	i = 0;
	name = NULL;
	content = NULL;
	while (env[i])
	{
		split_env(&name, &content, env);
		if (!better_strncmp(name, "SHLVL", ft_strlen("SHLVL")))
		{
			tmp = ft_itoa(ft_atoi(content) + 1);
			free(content);
			content = tmp;
		}
		else if (!better_strncmp(name, "PATH", ft_strlen("PATH")))
			data->paths = ft_split(content, ":");
		ft_envadd_back(&(data->loc_env), ft_envnew(name, content));
		i++;
	}
}

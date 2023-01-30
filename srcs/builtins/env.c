/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:22:57 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/30 21:39:15 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_error(char *str)
{
	ft_putstr_fd("env: ", 2);
	if (str[0] == '-')
	{
		ft_putstr_fd("options unavailable -- \'", 2);
		ft_putstr_fd(str + 1, 2);
		ft_putstr_fd("\'\n", 2);
		return (125);
	}
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': No such file or directory\n", 2);
	return (127);
}

int	ft_env(t_env *loc_env, char **cmd)
{
	t_env	*print_env;

	print_env = loc_env;
	if (cmd[1])
	{
		return (env_error(cmd[1]));
	}
	while (print_env)
	{
		if (print_env->content)
			printf("%s=%s\n", print_env->name, print_env->content);
		print_env = print_env->next;
	}
	return (0);
}

void	split_env(t_data *data, char **name, char **content, char *env)
{
	int	j;

	j = 0;
	while (env[j] != '=')
		j++;
	*name = ft_substr(data, env, 0, j);
	*content = ft_substr(data, env, j + 1, ft_strlen(env + j + 1));
}

void	update_env(char	**env, t_data *data)
{
	int		i;
	char	*name;
	char	*content;

	i = 0;
	name = NULL;
	content = NULL;
	free_split(data->paths);
	data->paths = NULL;
	while (env && env[i])
	{
		split_env(data, &name, &content, env[i]);
		if (!better_strncmp(name, "PATH", ft_strlen("PATH")))
			data->paths = ft_split(data, content, ":");
		i++;
		// free(name);
		// free(content);
	}
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
		split_env(data, &name, &content, env[i]);
		if (!better_strncmp(name, "SHLVL", ft_strlen("SHLVL")))
		{
			tmp = ft_itoa(data, ft_atoi(content) + 1);
			// free(content);
			content = tmp;
		}
		else if (!better_strncmp(name, "PATH", ft_strlen("PATH")))
			data->paths = ft_split(data, content, ":");
		ft_envadd_back(&(data->loc_env), ft_envnew(data, name, content, 1));
		i++;
	}
}

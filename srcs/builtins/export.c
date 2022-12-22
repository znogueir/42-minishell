/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:15 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/21 20:49:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	sort_export(t_data *data)
{
	int		env_len;
	t_env	*env_min;
	t_env	*next_min;
	t_env	*p_env;

	env_len = 0;
	p_env = data->loc_env;
	env_min = p_env;
	while (p_env)
	{
		if (ft_strcmp(env_min->name, p_env->name) > 0)
			env_min = p_env;
		p_env = p_env->next;
		env_len++;
	}
	env_len--;
	ft_printf("export %s=\"%s\"\n", env_min->name, env_min->content);
	while (--env_len)
	{
		p_env = data->loc_env;
		while (p_env && ft_strcmp(env_min->name, p_env->name) >= 0)
			p_env = p_env->next;
		next_min = p_env;
		// ft_printf("%s\n", next_min->name);
		while (p_env)
		{
			if (ft_strcmp(env_min->name, p_env->name) < 0 \
			&& ft_strcmp(p_env->name, next_min->name) < 0)
				next_min = p_env;
			p_env = p_env->next;
		}
		// ft_printf("%s\n", next_min->name);
		env_min = next_min;
		ft_printf("export %s=\"%s\"\n", env_min->name, \
		env_min->content);
		// env_len--;
	}
}

int	check_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (!((cmd[0] >= 'a' && cmd[0] <= 'z') || \
	(cmd[0] >= 'A' && cmd[0] <= 'Z') || cmd[0] == '_'))
	{
		g_exit = 1;
		return (write(2, "minishell: export: invalid identifier\n", 39), 1);
	}
	while (cmd[i] && cmd[i] != '=' && cmd[i] != '+')
	{
		if (!(is_alphanum(cmd[i]) || cmd[i] == '_'))
		{
			g_exit = 1;
			return (write(2, "minishell: export: invalid identifier\n", 39), 1);
		}
		i++;
	}
	if (cmd[i] == '+' && cmd[i + 1] != '=')
	{
		g_exit = 1;
		return (write(2, "minishell: export: invalid identifier\n", 39), 1);
	}
	return (0);
}

int	parse_export(char **cmd, t_data *data)
{
	int	i;
	int	j;

	j = 1;
	while (cmd[j])
	{
		i = 0;
		if (check_identifier(cmd[j]))
		{
			j++;
			g_exit = 1;
			continue ;
		}
		while (cmd[j][i] && cmd[j][i] != '=' && cmd[j][i] != '+')
			i++;
		if (cmd[j][i] && cmd[j][i] == '=')
			ft_export(data, ft_substr(cmd[j], 0, i), \
			ft_strdup(cmd[j] + i + 1), 0);
		else if (cmd[j][i] && cmd[j][i] == '+' && cmd[j][i + 1] == '=')
			ft_export(data, ft_substr(cmd[j], 0, i), \
			ft_strdup(cmd[j] + i + 2), 1);
		j++;
	}
	if (!cmd[1])
		sort_export(data);
	return (g_exit);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:15 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/02 19:08:28 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(t_data *data)
{
	int		env_len;
	t_env	*env_min;
	t_env	*next_min;
	t_env	*p_env;

	p_env = data->loc_env;
	env_min = p_env;
	env_len = get_env_len(&p_env, &env_min);
	while (--env_len > 0)
	{
		p_env = data->loc_env;
		while (p_env && ft_strcmp(env_min->name, p_env->name) >= 0)
			p_env = p_env->next;
		next_min = p_env;
		while (p_env)
		{
			if (ft_strcmp(env_min->name, p_env->name) < 0 \
			&& ft_strcmp(p_env->name, next_min->name) < 0)
				next_min = p_env;
			p_env = p_env->next;
		}
		env_min = next_min;
		print_export(env_min->name, env_min->content);
	}
}

int	check_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (!((cmd[0] >= 'a' && cmd[0] <= 'z') || \
	(cmd[0] >= 'A' && cmd[0] <= 'Z') || cmd[0] == '_'))
		return (ft_putstr_fd \
		("minishell: export: not a valid identifier\n", 2), 2);
	while (cmd[i] && cmd[i] != '=' && cmd[i] != '+')
	{
		if (!(is_alphanum(cmd[i]) || cmd[i] == '_'))
			return (ft_putstr_fd \
			("minishell: export: not a valid identifier\n", 2), 2);
		i++;
	}
	if (cmd[i] == '+' && cmd[i + 1] != '=')
		return (ft_putstr_fd \
		("minishell: export: not a valid identifier\n", 2), 2);
	return (0);
}

void	export_word(t_data *data, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '=' && cmd[i] != '+')
		i++;
	if (cmd[i] && cmd[i] == '=')
		ft_export(data, ft_substr(data, cmd, 0, i), \
		ft_strdup(data, cmd + i + 1), 0);
	else if (cmd[i] && cmd[i] == '+' && cmd[i + 1] == '=')
		ft_export(data, ft_substr(data, cmd, 0, i), \
		ft_strdup(data, cmd + i + 2), 1);
	else
		ft_export(data, ft_substr(data, cmd, 0, i), NULL, 0);
}

int	parse_export(char **cmd, t_data *data)
{
	int	j;

	j = 1;
	while (cmd[j])
	{
		if (cmd[j] && cmd[j][0] && cmd[j][0] == '-')
			return (ft_putstr_fd \
			("minishell: export: options unavailable\n", 2), 2);
		if (check_identifier(cmd[j]))
		{
			j++;
			g_exit = 1;
			continue ;
		}
		export_word(data, cmd[j++]);
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
		ft_free(name);
		if (append)
		{
			p_env->content = ft_strjoin(data, p_env->content, content);
			ft_free(content);
			return (0);
		}
		ft_free(p_env->content);
		p_env->content = content;
		return (0);
	}
	if (!content)
		return (ft_envadd_back(&(data->loc_env), \
		ft_envnew(data, name, content, 0)), 0);
	return (ft_envadd_back(&(data->loc_env), \
	ft_envnew(data, name, content, 1)), 1);
}

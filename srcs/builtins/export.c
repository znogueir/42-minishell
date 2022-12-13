/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:15 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/10 23:12:48 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (!((cmd[0] >= 'a' && cmd[0] <= 'z') || \
	(cmd[0] >= 'A' && cmd[0] <= 'Z')))
		return (write(2, "minishell: export: invalid identifier\n", 39), 1);
	while (cmd[i] && cmd[i] != '=' && cmd[i] != '+')
	{
		if (!is_alphanum(cmd[i]))
			return (write(2, "minishell: export: invalid identifier\n", 39), 1);
		i++;
	}
	if (cmd[i] == '+' && cmd[i + 1] != '=')
		return (write(2, "minishell: export: invalid identifier\n", 39), 1);
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
	return (0);
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

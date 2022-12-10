/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:22:49 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/15 17:22:50 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	swap_pwds(t_data *data)
{
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	char	*save_pwd;

	env_pwd = data->loc_env;
	env_oldpwd = data->loc_env;
	while (env_oldpwd && better_strncmp(env_oldpwd->name, "OLDPWD", 6))
		env_oldpwd = env_oldpwd->next;
	if (chdir(env_oldpwd->content) != 0)
		return (perror("minishell: cd"), 1);
	while (env_pwd && better_strncmp(env_pwd->name, "PWD", 3))
		env_pwd = env_pwd->next;
	save_pwd = env_pwd->content;
	env_pwd->content = env_oldpwd->content;
	env_oldpwd->content = save_pwd;
	return (0);
}

int	ft_cd(t_data *data, char *path)
{
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	char	*cd;
	char	*save_pwd;

	cd = NULL;
	env_pwd = data->loc_env;
	env_oldpwd = data->loc_env;
	ft_printf("my cd :\n");
	if (path[0] == '-' && !path[1])
		return (swap_pwds(data));
	else if (chdir(path) != 0)
		return (perror("minishell: cd"), 1);
	cd = getcwd(cd, 100);
	if (cd == NULL)
		return (1);
	while (env_pwd && better_strncmp(env_pwd->name, "PWD", 3))
		env_pwd = env_pwd->next;
	save_pwd = env_pwd->content;
	while (env_oldpwd && better_strncmp(env_oldpwd->name, "OLDPWD", 6))
		env_oldpwd = env_oldpwd->next;
	env_pwd->content = env_oldpwd->content;
	env_oldpwd->content = save_pwd;
	return (0);
}

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

char	*get_env_content(t_data *data, char *name)
{
	t_env	*env;

	env = data->loc_env;
	while (env && better_strncmp(env->name, name, ft_strlen(name)))
		env = env->next;
	return (ft_strdup(env->content));
}

int	parse_cd(t_data *data, char **cmd)
{
	char	*path;

	path = NULL;
	if (cmd[1] && cmd[2])
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (!cmd[1])
		path = get_env_content(data, "HOME");
	else if (cmd[1][0] == '-' && !cmd[1][1])
		path = get_env_content(data, "OLDPWD");
	else if (cmd[1][0] == '~')
		path = ft_strjoin(get_env_content(data, "HOME"), cmd[1] + 1);
	else
		path = ft_strdup(cmd[1]);
	if (chdir(path) != 0)
		return (free(path), perror("minishell: cd"), 1);
	return (free(path), 0);
}

int	ft_cd(t_data *data, char **cmd)
{
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	char	*cd;
	char	*save_pwd;

	cd = NULL;
	env_pwd = data->loc_env;
	env_oldpwd = data->loc_env;
	if (parse_cd(data, cmd))
		return (1);
	cd = getcwd(cd, 100);
	if (cd == NULL)
		return (1);
	while (env_pwd && better_strncmp(env_pwd->name, "PWD", 3))
		env_pwd = env_pwd->next;
	save_pwd = ft_strdup(env_pwd->content);
	while (env_oldpwd && better_strncmp(env_oldpwd->name, "OLDPWD", 6))
		env_oldpwd = env_oldpwd->next;
	free(env_pwd->content);
	free(env_oldpwd->content);
	env_pwd->content = cd;
	env_oldpwd->content = save_pwd;
	return (0);
}

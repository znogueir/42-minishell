/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:22:49 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/03 20:29:25 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_content(t_data *data, char *name)
{
	t_env	*env;

	env = data->loc_env;
	while (env && better_strncmp(env->name, name, ft_strlen(name)))
		env = env->next;
	if (env)
		return (ft_strdup(data, env->content));
	return (NULL);
}

t_env	*get_pointer_env(t_data *data, char *name)
{
	t_env	*env;

	env = data->loc_env;
	while (env && better_strncmp(env->name, name, ft_strlen(name)))
		env = env->next;
	if (!env)
	{
		ft_export(data, ft_strdup(data, name), NULL, 0);
		env = data->loc_env;
		while (env && better_strncmp(env->name, name, ft_strlen(name)))
			env = env->next;
	}
	return (env);
}

int	check_cd_expand(t_data *data, char **cmd, char **path)
{
	if (!cmd[1])
	{
		*path = get_env_content(data, "HOME");
		if (*path == NULL)
			return (write(2, "minishell: cd: HOME not set\n", 29), -1);
		return (1);
	}
	else if (cmd[1][0] == '-' && !cmd[1][1])
	{
		*path = get_env_content(data, "OLDPWD");
		if (*path == NULL)
			return (write(2, "minishell: cd: OLDPWD not set\n", 30), -1);
		if (*path[0] == '\0')
			return (printf("\n"), ft_free(*path), -1);
		return (2);
	}
	return (0);
}

int	parse_cd(t_data *data, char **cmd)
{
	char	*path;
	int		cd_expand;

	path = NULL;
	if (cmd[1] && cmd[2])
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (cmd[1] && cmd[1][0] == '\0')
		return (1);
	cd_expand = check_cd_expand(data, cmd, &path);
	if (cd_expand == -1)
		return (1);
	if (!cd_expand)
		path = ft_strdup(data, cmd[1]);
	if (chdir(path) != 0)
		return (ft_free(path), perror("minishell: cd"), 1);
	if (cd_expand == 2)
		printf("%s\n", path);
	return (ft_free(path), 0);
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
	ft_add_to_mem(data, cd);
	if (cd == NULL)
		return (perror("cd"), 1);
	env_pwd = get_pointer_env(data, "PWD");
	env_oldpwd = get_pointer_env(data, "OLDPWD");
	save_pwd = ft_strdup(data, env_pwd->content);
	ft_free(env_pwd->content);
	ft_free(env_oldpwd->content);
	env_pwd->content = cd;
	env_oldpwd->content = save_pwd;
	return (0);
}

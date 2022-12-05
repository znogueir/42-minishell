/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:35:15 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/05 00:27:29 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*str;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof (char));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_get_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ":"));
		i++;
	}
	return (NULL);
}

int	check_path(char *prog, char *cmdpath)
{
	if (access(cmdpath, F_OK) == 0)
	{
		if (access(cmdpath, X_OK) == 0)
			return (0);
		return (ft_permission_denied(prog));
		free(cmdpath);
	}
	return (1);
}

char	*ft_join_path(char *path, char *prog)
{
	char	*cmd;
	char	*cmdpath;

	cmd = ft_strjoin_2("/", prog);
	cmdpath = ft_strjoin_2(path, cmd);
	free(cmd);
	return (cmdpath);
}	

char	*get_valid_path(char **env, char **prog)
{
	char	**paths;
	char	*cmdpath;
	int		i;
	int		ext;

	i = 0;
	ext = 1;
	paths = ft_get_paths(env);
	if (!paths)
		return (NULL);
	cmdpath = ft_join_path(paths[0], prog[0]);
	while (paths[i] && ext == 1)
	{
		free(cmdpath);
		cmdpath = ft_join_path(paths[i++], prog[0]);
		ext = check_path(prog[0], cmdpath);
	}
	if (!paths[i] && ext == 1)
		ext = ft_command_not_found(prog[0]);
	if (ext == 0 && cmdpath)
		return (cmdpath);
	free_things(paths, prog, cmdpath);
	exit(ext);
}

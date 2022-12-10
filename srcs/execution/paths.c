/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:35:15 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/09 19:38:34 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	cmd = ft_strjoin(ft_strdup("/"), prog);
	cmdpath = ft_strjoin(ft_strdup(path), cmd);
	free(cmd);
	return (cmdpath);
}	

char	*get_valid_path(t_data *data, char **prog)
{
	char	*cmdpath;
	int		i;
	int		ext;

	i = 0;
	ext = 1;
	if (!data->paths)
		return (NULL);
	cmdpath = ft_join_path(data->paths[0], prog[0]);
	while (data->paths[i] && ext == 1)
	{
		free(cmdpath);
		cmdpath = ft_join_path(data->paths[i++], prog[0]);
		ext = check_path(prog[0], cmdpath);
	}
	if (!data->paths[i] && ext == 1)
		ext = ft_command_not_found(prog[0]);
	if (ext == 0 && cmdpath)
		return (cmdpath);
	free(cmdpath);
	ft_exit_fork(data, prog, ext);
	exit(1);
}

char	*get_valid_cmd(t_data *data, char **command, int *ext)
{
	char	*validcmd;

	if (!command || !command[0])
		validcmd = NULL;
	else if (command[0][0] == '.' || command[0][0] == '/'
		|| command[0][1] == '/')
	{
		validcmd = ft_strdup(command[0]);
		*ext = check_path(validcmd, validcmd);
		if (*ext == 1)
			*ext = ft_no_such_file(validcmd);
	}
	else
		validcmd = get_valid_path(data, command);
	return (validcmd);
}
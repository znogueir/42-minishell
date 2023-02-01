/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:35:15 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/01 23:38:21 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(char *prog, char *cmdpath)
{
	if (access(cmdpath, F_OK) == 0)
	{
		if (access(cmdpath, X_OK) == 0)
			return (0);
		return (ft_permission_denied(prog));
		ft_free(cmdpath);
	}
	return (1);
}

char	*ft_join_path(t_data *data, char *path, char *prog)
{
	char	*cmd;
	char	*cmdpath;

	cmd = ft_strjoin(data, ft_strdup(data, "/"), prog);
	cmdpath = ft_strjoin(data, ft_strdup(data, path), cmd);
	ft_free(cmd);
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
	cmdpath = ft_join_path(data, data->paths[0], prog[0]);
	while (data->paths[i] && ext == 1)
	{
		ft_free(cmdpath);
		cmdpath = ft_join_path(data, data->paths[i++], prog[0]);
		ext = check_path(prog[0], cmdpath);
	}
	if (!data->paths[i] && ext == 1)
		ext = ft_command_not_found(prog[0]);
	if (ext == 0 && cmdpath)
		return (cmdpath);
	ft_free(cmdpath);
	g_exit = ext;
	// ft_exit_fork(data, prog, ext);
	ft_quit(data);
	return (NULL);
}

char	*get_valid_cmd(t_data *data, char **command, int *ext)
{
	char	*validcmd;

	if (!command || !command[0])
		validcmd = NULL;
	else if (command[0][0] == '.' || command[0][0] == '/'
		|| command[0][1] == '/')
	{
		validcmd = ft_strdup(data, command[0]);
		*ext = check_path(validcmd, validcmd);
		if (*ext == 1)
			*ext = ft_no_such_file(validcmd);
		if (*ext == ft_is_directory(validcmd))
			return (validcmd);
	}
	else
	{
		validcmd = get_valid_path(data, command);
	}
	return (validcmd);
}

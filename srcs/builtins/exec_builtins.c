/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:12:32 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/02 18:55:33 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(char **command, t_data *data)
{
	if (!better_strncmp(command[0], "cd", 2))
		return (ft_cd(data, command));
	else if (!better_strncmp(command[0], "echo", 4))
		return (ft_echo(command, 1));
	else if (!better_strncmp(command[0], "env", 3))
		return (ft_env(data->loc_env, command));
	else if (!better_strncmp(command[0], "exit", 4))
		return (ft_exit(data, command));
	else if (!better_strncmp(command[0], "export", 6))
		return (parse_export(command, data));
	else if (!better_strncmp(command[0], "pwd", 3))
		return (ft_pwd());
	else if (!better_strncmp(command[0], "unset", 5))
		return (ft_unset(data, command));
	return (0);
}

int	is_builtin(char **command)
{
	if (!command[0])
		return (0);
	if (!better_strncmp(command[0], "cd", 2))
		return (1);
	else if (!better_strncmp(command[0], "echo", 4))
		return (1);
	else if (!better_strncmp(command[0], "env", 3))
		return (1);
	else if (!better_strncmp(command[0], "exit", 4))
		return (1);
	else if (!better_strncmp(command[0], "export", 6))
		return (1);
	else if (!better_strncmp(command[0], "pwd", 3))
		return (1);
	else if (!better_strncmp(command[0], "unset", 5))
		return (1);
	return (0);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("[%s]\n", tab[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:12:32 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/08 20:12:34 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(char **command, t_data *data)
{
	if (!better_strncmp(command[0], "cd", 2))
		return (ft_cd(data, command[1]), 1);
	else if (!better_strncmp(command[0], "echo", 4))
		return (ft_echo(command, 1), 1);
	else if (!better_strncmp(command[0], "env", 3))
		return (ft_env(data->loc_env), 1);
	else if (!better_strncmp(command[0], "exit", 4))
		return (ft_exit(data), 1);
	else if (!better_strncmp(command[0], "export", 6))
		return (parse_export(command[1], data), 1);
	else if (!better_strncmp(command[0], "pwd", 3))
		return (ft_pwd(), 1);
	else if (!better_strncmp(command[0], "unset", 5))
		return (ft_unset(data, command), 1);
	return (0);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

// void	execute_builtins(char **command, t_data *data)
// {
// 	print_tab(command);
// 	free_split(command);
// 	exit(0);
// }

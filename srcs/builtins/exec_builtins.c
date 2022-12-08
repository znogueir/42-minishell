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

int	is_builtin(char **command)
{
	if (!better_strncmp(command[0], "cd", 2))
		return (1);
	if (!better_strncmp(command[0], "echo", 4))
		return (1);
	if (!better_strncmp(command[0], "env", 3))
		return (1);
	if (!better_strncmp(command[0], "exit", 4))
		return (1);
	if (!better_strncmp(command[0], "export", 5))
		return (1);
	if (!better_strncmp(command[0], "pwd", 3))
		return (1);
	if (!better_strncmp(command[0], "unset", 5))
		return (1);
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

void	execute_builtins(char **command)
{
	print_tab(command);
	free_split(command);
	exit(0);
}

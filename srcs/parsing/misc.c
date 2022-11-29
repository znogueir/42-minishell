/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:53:28 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/19 17:53:30 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	better_strncmp(char *s1, char *s2, int size)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != (size_t)size || ft_strlen(s2) != (size_t)size ||\
	 !s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && i < size)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_alphanum(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || \
	(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	print_colors(void)
{
	ft_printf("----test colors :----\n");
	ft_printf(PINK"█████ - PINK%s\n", RES_COL);
	ft_printf(PURPLE"█████ - PURPLE%s\n", RES_COL);
	ft_printf(BLUE"█████ - BLUE%s\n", RES_COL);
	ft_printf(CYAN"█████ - CYAN%s\n", RES_COL);
	ft_printf(GREEN"█████ - GREEN%s\n", RES_COL);
	ft_printf(YELLOW"█████ - YELLOW%s\n", RES_COL);
	ft_printf(ORANGE"█████ - ORANGE%s\n", RES_COL);
	ft_printf(RED"█████ - RED%s\n---------------------------", RES_COL);
	ft_printf("\n%s█%s█%s█%s█%s█%s█%s█%s█%s\n", \
	PINK, PURPLE, BLUE, CYAN, GREEN, YELLOW, ORANGE, RED, RES_COL);
}

void	check_builtins(t_data *data)
{
	ft_cd("test");
	ft_echo("test", 1);
	ft_pwd();
	ft_env(data->loc_env);
	ft_export(data, ft_strdup("name"), ft_strdup("content"));
	ft_env(data->loc_env);
	ft_unset(data, "nam");
	ft_env(data->loc_env);
	ft_unset(data, "namez");
	ft_env(data->loc_env);
	ft_unset(data, "name");
	ft_env(data->loc_env);
	ft_exit();
	print_colors();
}

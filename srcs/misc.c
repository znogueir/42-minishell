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

#include "../includes/minishell.h"

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
	ft_env(data->loc_env);
	ft_exit();
	ft_export(data, "name", "content");
	ft_pwd();
	ft_unset(data, "name");
	print_colors();
}

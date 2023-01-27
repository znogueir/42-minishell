/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:25:40 by ionorb            #+#    #+#             */
/*   Updated: 2023/01/27 15:18:36 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*break_malloc(int size)
{
	// cur_breakpoint++;
	// printf("breakpoint: %d, cur_breakpoint: %d\n",
	// 	break_malloc_at, cur_breakpoint);
	if (break_malloc_at == cur_breakpoint)
		return (NULL);
	return (malloc(size));
}

void	print_list(t_cmdline *cmd)
{
	if (cmd)
		ft_printf("\n");
	while (cmd)
	{
		ft_printf("\t{%s%s%s}", ORANGE, cmd->content, RES_COL);
		ft_printf(" - type : %s\n" RES_COL, convert_type(cmd->type));
		cmd = cmd->next;
	}
	if (cmd)
		ft_printf("\n");
}

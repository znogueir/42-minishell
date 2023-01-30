/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:25:40 by ionorb            #+#    #+#             */
/*   Updated: 2023/01/30 21:39:17 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*break_malloc(int size)
{
	cur_breakpoint++;
	printf("breakpoint: %d, cur_breakpoint: %d\n",
		break_malloc_at, cur_breakpoint);
	if (break_malloc_at == cur_breakpoint)
		return (NULL);
	return (malloc(size));
}

void	print_list(t_cmdline *cmd)
{
	if (cmd)
		printf("\n");
	while (cmd)
	{
		printf("\t{%s%s%s}", ORANGE, cmd->content, RES_COL);
		printf(" - type : %s\n" RES_COL, convert_type(cmd->type));
		cmd = cmd->next;
	}
	if (cmd)
		printf("\n");
}

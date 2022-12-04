/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:16:09 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/04 17:39:12 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_token_type(char *token)
{
	if (!better_strncmp(token, "|", 1))
		return (PIPE);
	else if (!better_strncmp(token, "\n", 1))
		return (NEWLINES);
	else if (!better_strncmp(token, ">>", 2))
		return (APPEND);
	else if (!better_strncmp(token, "<<", 2))
		return (H_DOC);
	else if (!better_strncmp(token, "<>", 2))
		return (LESSGREAT);
	else if (!better_strncmp(token, "<", 1))
		return (LESS);
	else if (!better_strncmp(token, ">", 1))
		return (GREAT);
	return (0);
}

char	*convert_type(int type)
{
	if (type == 0)
		return (CYAN"WORD"RES_COL);
	else if (type == 1)
		return (PURPLE"PIPE"RES_COL);
	else if (type == 2)
		return (RED"LESS"RES_COL);
	else if (type == 3)
		return (YELLOW"GREAT"RES_COL);
	else if (type == 4)
		return (BLUE"H_DOC"RES_COL);
	else if (type == 5)
		return (PINK"APPEND"RES_COL);
	else if (type == 6)
		return (ORANGE"LESSGREAT"RES_COL);
	else if (type == 7)
		return (GREEN"NEWLINES"RES_COL);
	return ("NDEF");
}

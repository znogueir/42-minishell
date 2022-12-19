/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:06:26 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(int type)
{
	if (type >= LESS && type <= LESSGREAT)
		return (1);
	return (0);
}

int	check_pipes(t_cmdline *cmd)
{
	t_cmdline	*p_cmd;

	p_cmd = cmd;
	if (p_cmd && p_cmd->type == PIPE)
		return (1);
	while (p_cmd)
	{
		if (p_cmd->type == PIPE && p_cmd->next && p_cmd->next->type == PIPE)
			return (1);
		if (p_cmd->type == PIPE && !p_cmd->next)
			return (1);
		if (is_redir(p_cmd->type) && p_cmd->next && p_cmd->next->type == PIPE)
			return (1);
		p_cmd = p_cmd->next;
	}
	return (0);
}

int	check_redirs(t_cmdline *cmd)
{
	t_cmdline	*p_cmd;

	p_cmd = cmd;
	while (p_cmd)
	{
		if (is_redir(p_cmd->type) && p_cmd->next && is_redir(p_cmd->next->type))
			return (1);
		if (is_redir(p_cmd->type) && !p_cmd->next)
			return (1);
		p_cmd = p_cmd->next;
	}
	return (0);
}

int	ft_parser(t_data *data)
{
	if (check_pipes(data->cmd))
		return (write_error("syntax error near unexpected token '|'\n"), 1);
	if (check_redirs(data->cmd))
		return (write_error("syntax error near unexpected redir token\n"), 1);
	return (0);
}

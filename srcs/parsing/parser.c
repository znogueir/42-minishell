/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:06:26 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/21 20:24:01 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(char *error_msg, char *token)
{
	ft_putstr_fd(ERR_PRE, 2);
	ft_putstr_fd(error_msg, 2);
	if (token)
	{
		ft_putstr_fd(token, 2);
		ft_putstr_fd("\'\n", 2);
	}
}

int	check_quote(char *str)
{
	char	end_quote;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != 39 && str[i] != 34)
		i++;
	if (str[i] == 39 || str[i] == 34)
		end_quote = str[i];
	else
		return (0);
	i++;
	while (str[i] && str[i] != end_quote)
		i++;
	if (!str[i])
		return (1);
	return (check_quote(str + i + 1));
}

int	check_errors(char *line)
{
	if (check_quote(line))
	{
		write_error(": quote missing\n", NULL);
		g_exit = 2;
		return (1);
	}
	return (0);
}

int	is_redir(int type)
{
	if (type >= LESS && type <= LESSGREAT)
		return (1);
	return (0);
}

int	ft_parser(t_data *data)
{
	t_cmdline	*p_cmd;

	p_cmd = data->cmd;
	if (p_cmd && p_cmd->type == PIPE)
		return (write_error(" near unexpected token \'", "|"), 2);
	while (p_cmd)
	{
		if (p_cmd->type == PIPE && p_cmd->next && p_cmd->next->type == PIPE)
			return (write_error(" near unexpected token \'", "|"), 2);
		if (p_cmd->type == PIPE && !p_cmd->next)
			return (write_error(" near unexpected token \'", "newline"), 2);
		if (is_redir(p_cmd->type) && p_cmd->next && p_cmd->next->type != WORD)
			return (write_error(" near unexpected token \'", \
			p_cmd->next->content), 2);
		if (is_redir(p_cmd->type) && !p_cmd->next)
			return (write_error(" near unexpected token \'", "newline"), 2);
		p_cmd = p_cmd->next;
	}
	return (0);
}

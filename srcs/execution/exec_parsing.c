/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:50:19 by yridgway          #+#    #+#             */
/*   Updated: 2022/11/30 16:50:20 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	display_cmdtable(t_cmdtable *table)
{
	int	i;

	i = 0;
	ft_putstr_fd("\ncmdtable:\n", 2);
	while (table)
	{
		if (table->operator)
		{
			ft_putstr_fd(table->operator, 2);
			write(2, " ", 1);
		}
		else if (table->cmd)
		{
			i = 0;
			write(2, "[", 1);
			while (table->cmd[i + 1])
			{
				ft_putstr_fd(table->cmd[i++], 2);
				write(2, " ", 1);
			}
			ft_putstr_fd(table->cmd[i], 2);
			write(2, "] ", 2);
		}
		table = table->next;
	}
	write(2, "\n\n", 2);
}

int	ft_is_redir(int i)
{
	if (i >= 2 && i <= 5)
		return (1);
	return (0);
}

void	ft_make_cmd_array(t_data *data, t_cmdline *cmdline, int count)
{
	int		i;
	char	**cmd;

	i = 0;
	
	cmd = malloc(sizeof (char *) * (count + 1));
	while (i < count)
	{
		if (ft_is_redir(cmdline->type))
			cmdline = cmdline->next->next;
		cmd[i++] = ft_strdup(cmdline->content);
		cmdline = cmdline->next;
	}
	cmd[i] = NULL;
	ft_tableadd_back(&data->cmdtable, ft_tablenew(cmd, NULL, WORD));
}

void	make_cmdtable(t_data *data)
{
	int			count;
	t_cmdline	*temp;
	t_cmdline	*line;

	line = data->cmd;
	while (line->type != NEWLINE)
	{
		count = 0;
		temp = line;
		if (!line)
			break ;
		while (line && (line->type == WORD || ft_is_redir(line->type)))
		{
			if (ft_is_redir(line->type))
			{
				ft_tableadd_back(&data->cmdtable, ft_tablenew(NULL,
						ft_strjoin(ft_strdup(line->content), line->next->content), line->type));
				line = line->next;
			}
			else
				count++;
			line = line->next;
		}
		if (count > 0)
			ft_make_cmd_array(data, temp, count);
		while (line && line->type != WORD && line->type != NEWLINE)
		{
			ft_tableadd_back(&data->cmdtable, ft_tablenew(NULL,
					ft_strdup(line->content), line->type));
			line = line->next;
		}
	}
}

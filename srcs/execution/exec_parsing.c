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

	while (table)
	{
		i = 0;
		printf("__________________________________________\n");
		printf("infile: %s\n", table->infile);
		printf("outfile: %s\n", table->outfile);
		printf("outfd: %d\n", table->outfd);
		printf("infd: %d\n", table->infd);
		while (table->cmd[i])
			printf("%s ", table->cmd[i++]);
		printf("\n");
		table = table->next;
	}
}

void	ft_make_cmd_array(t_cmdtable *table, t_cmdline *cmdline, int count)
{
	int		i;

	i = 0;
	
	table->cmd = malloc(sizeof (char *) * (count + 1));
	while (i < count)
	{
		if (is_redir(cmdline->type))
			cmdline = cmdline->next->next;
		else
		{
			table->cmd[i++] = ft_strdup(cmdline->content);
			cmdline = cmdline->next;
		}
	}
	table->cmd[i] = NULL;;
}

void	ft_fill_files_v2(t_cmdtable *table, t_cmdline **line)
{
	if ((*line)->type == LESS)
	{
		free(table->infile);
		table->infile = ft_strdup((*line)->next->content);
		table->infd = open((*line)->next->content, O_RDONLY);
		if (table->infd == -1)
			return (-1);
	}
	if ((*line)->type == GREAT)
	{
		free(table->outfile);
		table->outfile = ft_strdup((*line)->next->content);
		table->outfd = open((*line)->next->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (table->outfd == -1)
			return (-1);
	}
	*line = (*line)->next;
}

t_cmdtable	*get_last(t_cmdtable *table)
{
	while (table->next)
	{
		table = table->next;
	}
	return (table);
}

t_cmdtable	*new_table(void)
{
	t_cmdtable	*table;

	table = malloc(sizeof(t_cmdtable));
	table->infd = 0;
	table->outfd = 1;
	table->infile = NULL;
	table->outfile = NULL;
	table->cmd = NULL;
	table->next = NULL;
	return (table);
}

void	make_cmdtable(t_data *data)
{
	t_cmdline	*line;
	t_cmdline	*temp;
	t_cmdtable	*cur_tab;
	int			count;

	line = data->cmd;
	while (line && line->type != NEWLINE)
	{
		ft_tableadd_back(&data->cmdtable, new_table());
		cur_tab = get_last(data->cmdtable);
		temp = line;
		count = 0;
		while (line && line->type != PIPE)
		{
			if (is_redir(line->type))
				ft_fill_files_v2(cur_tab, &line);
			else if (line->type == WORD)
				count++;
			line = line->next;
		}
		ft_make_cmd_array(cur_tab, temp, count);
		if (line)
			line = line->next;
	}
}

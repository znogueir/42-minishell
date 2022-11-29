/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:46:37 by yridgway          #+#    #+#             */
/*   Updated: 2022/11/29 18:46:41 by yridgway         ###   ########.fr       */
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

void	ft_error_opening(t_filelist **filelist, char *filename)
{
	perror(filename);
	while (*filelist)
	{
		if ((*filelist)->fd != -1)
			close((*filelist)->fd);
		*filelist = (*filelist)->next;
	}
}

void	open_redir_files(t_data *data, t_cmdtable *table)
{
	t_filelist *filelist;

	while (table)
	{
		if (table->type == GREAT)
			ft_fileadd_back(&data->filelist,
				ft_filenew(open(table->operator + 1, O_RDWR | O_CREAT | O_TRUNC, 0644),
					ft_strdup(table->operator + 1)));
		else if (table->type == LESS)
			ft_fileadd_back(&data->filelist, ft_filenew(open(table->operator + 1, O_RDONLY),
				ft_strdup(table->operator + 1)));
		table = table->next;
	}
	filelist = data->filelist;
	while (filelist)
	{
		if (filelist->fd < 0)
			ft_error_opening(&filelist, filelist->filename);
		else
			filelist = filelist->next;
	}
}

int	ft_executor(t_data *data)
{
	make_cmdtable(data);
	display_cmdtable(data->cmdtable);
	//display_cmdtable(data->cmdtable);
	open_redir_files(data, data->cmdtable);
	// while(data->filelist)
	// {
	// 	ft_putstr_fd(data->filelist->filename, 2);
	// 	write(2, "\n", 1);
	// 	data->filelist = data->filelist->next;
	// }
	return (0);
}

//echo banana < in | ls < bingf | < bing
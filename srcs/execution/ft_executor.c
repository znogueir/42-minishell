# include "../../includes/minishell.h"

void	display_cmdtable(t_cmdtable **table)
{
	int	i;

	i = 0;
	ft_putstr_fd("\ncmdtable:\n", 2);
	while (*table)
	{
		if ((*table)->operator)
		{
			ft_putstr_fd((*table)->operator, 2);
			write(2, " ", 1);
		}
		else if ((*table)->cmd)
		{
			i = 0;
			write(2, "[", 1);
			while ((*table)->cmd[i + 1])
			{
				ft_putstr_fd((*table)->cmd[i++], 2);
				write(2, " ", 1);
			}
			ft_putstr_fd((*table)->cmd[i], 2);
			write(2, "] ", 2);
		}
		(*table) = (*table)->next;
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
	ft_tableadd_back(&data->cmdtable, ft_tablenew(cmd, NULL));
}

void	make_cmdtable(t_data *data)
{
	int	count;
	t_cmdline *temp;

	while (data->cmd->type != NEWLINE)
	{
		count = 0;
		temp = data->cmd;
		if (!data->cmd)
			break ;
		while (data->cmd && (data->cmd->type == WORD || ft_is_redir(data->cmd->type)))
		{
			if (ft_is_redir(data->cmd->type))
			{
				ft_tableadd_back(&data->cmdtable, ft_tablenew(NULL,
						ft_strjoin(data->cmd->content, data->cmd->next->content)));
				data->cmd = data->cmd->next;
			}
			else
				count++;
			data->cmd = data->cmd->next;
		}
		if (count > 0)
			ft_make_cmd_array(data, temp, count);
		while (data->cmd && data->cmd->type != WORD && data->cmd->type != NEWLINE)
		{
			ft_tableadd_back(&data->cmdtable, ft_tablenew(NULL, ft_strdup(data->cmd->content)));
			data->cmd = data->cmd->next;
		}
	}
}

int	ft_executor(t_data *data)
{
	data->cmdtable = NULL;
	make_cmdtable(data);
	display_cmdtable(&data->cmdtable);
	open_redir_files();
}

// void	ft_make_cmd_array(t_data *data, t_cmdline *cmdline, int count)
// {
// 	int		i;
// 	char	**cmd;

// 	i = 0;
	
// 	cmd = malloc(sizeof (char *) * (count + 1));
// 	while (i < count)
// 	{
// 		cmd[i++] = ft_strdup(cmdline->content);
// 		cmdline = cmdline->next;
// 	}
// 	cmd[i] = NULL;
// 	ft_tableadd_back(&data->cmdtable, ft_tablenew(cmd, NULL));
// }

// void	make_cmdtable(t_data *data)
// {
// 	int	count;
// 	t_cmdline *temp;

// 	while (data->cmd->type != NEWLINE)
// 	{
// 		count = 0;
// 		temp = data->cmd;
// 		if (!data->cmd)
// 			break ;
// 		while (data->cmd && data->cmd->type == WORD)
// 		{
// 			count++;
// 			data->cmd = data->cmd->next;
// 		}
// 		if (count > 0)
// 			ft_make_cmd_array(data, temp, count);
// 		while (data->cmd && data->cmd->type != WORD && data->cmd->type != NEWLINE)
// 		{
// 			ft_tableadd_back(&data->cmdtable, ft_tablenew(NULL, ft_strdup(data->cmd->content)));
// 			data->cmd = data->cmd->next;
// 		}
// 	}
// }
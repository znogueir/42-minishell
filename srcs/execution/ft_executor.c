# include "../../includes/minishell.h"

void	ft_make_cmd_array(t_data *data, t_cmdline *cmdline, int count)
{
	int		i;
	char	**cmd;

	i = 0;
	
	cmd = malloc(sizeof (char *) * (count + 1));
	while (i < count)
	{
		cmd[i++] = ft_strdup(cmdline->content);
		cmdline = cmdline->next;
	}
	cmd[i] = NULL;
	ft_tableadd_back(&data->cmdtable, ft_tablenew(cmd, NULL));
	// i = 0;
	// while (data->cmdtable->next->cmd[i])
	// 	printf("cmd1: %s\n", data->cmdtable->next->cmd[i++]);
}

void	ft_make_operator(t_data *data, char *operator)
{
	ft_tableadd_back(&data->cmdtable, ft_tablenew(NULL, ft_strdup(operator)));
}

void	make_cmdtable(t_data *data)//, t_cmdline *cmdline, t_cmdtable *cmdtable)
{
	int	count;
	t_cmdline *temp;

	while (data->cmd->type != NEWLINE)
	{
		count = 0;
		temp = data->cmd;
		if (!data->cmd)
			break ;
		while (data->cmd && data->cmd->type == WORD)
		{
			count++;
			data->cmd = data->cmd->next;
		}
		if (count > 0)
		{
			ft_make_cmd_array(data, temp, count);
		}
		while (data->cmd && data->cmd->type != WORD && data->cmd->type != NEWLINE)
		{
			ft_make_operator(data, data->cmd->content);
			data->cmd = data->cmd->next;
		}
	}
}

int	ft_executor(t_data *data)
{
	int	i;
	// t_cmdtable	*temp;

	data->cmdtable = NULL;//ft_tablenew(NULL, NULL);
	make_cmdtable(data);
	while (data->cmdtable)
	{
		if (data->cmdtable->operator)
		{
			ft_putstr_fd(data->cmdtable->operator, 2);
			write(2, " ", 1);
		}
		else if (data->cmdtable->cmd)
		{
			i = 0;
			//write(2, "[", 1);
			while (data->cmdtable->cmd[i])
			{
				ft_putstr_fd(data->cmdtable->cmd[i++], 2);
				write(2, " ", 1);
			}
			//write(2, "]", 1);
		}
		data->cmdtable = data->cmdtable->next;
	}
	write(2, "\n", 1);
}
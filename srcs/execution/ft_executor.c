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
	i = 0;
	while (data->cmdtable->cmd[i])
		printf("cmd1: %s\n", data->cmdtable->cmd[i++]);
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
		while (data->cmd && data->cmd->type == PIPE)
		{
			printf("content: %s\n", data->cmd->content);
			ft_make_operator(data, data->cmd->content);
			data->cmd = data->cmd->next;
		}
		// cmdline = cmdline->next;
		// if (cmdline->type == WORD)
		// {
		// 	ft_append_cmd(cmdtable, cmdline->content);
		// 	cmdline = cmdline->next;
		// }
		// if (cmdline->type == PIPE)
		// {
		// 	cmdtable->next = ft_tablenew();
		// 	cmdtable = cmdtable->next;

		// }
		//data->cmd = data->cmd->next;
	}
}

int	ft_executor(t_data *data)
{
	int	i;
	// t_cmdtable	*temp;

	data->cmdtable = NULL;
	make_cmdtable(data);
	while (data->cmdtable)
	{
		if (data->cmdtable->operator)
			printf("operator: %s\n", data->cmdtable->operator);
		else
		{
			i = 0;
			while (data->cmdtable->cmd[i])
				printf("cmd[%d]: %s\n", i, data->cmdtable->cmd[i++]);
		}
		data->cmdtable = data->cmdtable->next;
	}
	while (data->cmdtable)
	{
		if (data->cmdtable->operator)
			printf("operator: %s\n", data->cmdtable->operator);
		else
		{
			i = 0;
			while (data->cmdtable->cmd[i])
				printf("cmd[%d]: %s\n", i, data->cmdtable->cmd[i++]);
		}
		data->cmdtable = data->cmdtable->next;
	}
}
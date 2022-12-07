/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:46:37 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/07 20:39:47 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_cmdtable(t_cmdtable *table)
{
	int			i;
	t_filelist	*infile;
	t_filelist	*outfile;

	while (table)
	{
		ft_printf("\n");
		infile = table->infile;
		outfile = table->outfile;
		i = 0;
		printf("\tinfile: ");
		while (table && infile) // && table->infile->next)
		{
			printf("[%d] %s, ", infile->fd, infile->filename);
			infile = infile->next;
		}
		printf("\n\toutfile: ");
		while (table && outfile) // && table->outfile->next)
		{
			printf("[%d] %s, ", outfile->fd, outfile->filename);
			outfile = outfile->next;
		}
		printf("\n\tcmd: ");
		while (table->cmd[i])
			printf("%s ", table->cmd[i++]);
		printf("\n\tstatus: %d\n", table->status);
		table = table->next;
		ft_printf("\n");
	}
}

char	**ft_arr_dup(char **arr)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	i = 0;
	if (!arr)
		return (NULL);
	while (arr[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		copy[i] = ft_strdup(arr[i]);
		i++;
	}
	copy[i] = NULL;
	//ft_putstr_fd(copy[0], 2);
	return (copy);
}

int	ft_check_fds(t_filelist *outfile, t_filelist *infile)
{
	if (!infile || !outfile || (outfile->fd != -1 && infile->fd != -1))
		return (1);
	else if (outfile->fd == -1 && infile->fd == -1)
	{
		if (outfile->order < infile->order)
			perror(outfile->filename);
		else
			perror(infile->filename);
	}
	else if (outfile->fd == -1)
		perror(outfile->filename);
	else
		perror(infile->filename);
	return (0);
}

int	ft_pipex(t_data *data, char **env)
{
	t_cmdtable	*table;
	t_filelist	*outfile;
	t_filelist	*infile;
	int			insave;

	table = data->cmdtable;
	insave = dup(0);
	while (table)
	{
		//write(2, "what\n", 5);
		infile = file_get_last(table->infile);
		outfile = file_get_last(table->outfile);
		if (ft_check_fds(outfile, infile))
		{
			ft_pipe(table, ft_arr_dup(table->cmd), env);
		}
		table = table->next;
	}
	dup2(insave, 0);
	return (1);
}

int	ft_executor(t_data *data, char **env)
{
	(void)env;
	data->cmdtable = NULL;
	make_cmdtable(data);
	//ft_putstr_fd("------pipex------", 2);
	ft_pipex(data, env);
	//close_files(data->cmdtable);
	if (data->cmdtable)
		display_cmdtable(data->cmdtable);
	free_table(data->cmdtable);
	return (0);
}

//echo banana < in | ls < bingf | < bing
//<< EOF << banana >out1(nopermissions) ls -la <in <<yo <jfksj
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:46:37 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/05 01:35:23 by yridgway         ###   ########.fr       */
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
		infile = table->infile;
		outfile = table->outfile;
		i = 0;
		printf("---------------------------------------------\n");
		printf("infile: ");
		while (table && infile) // && table->infile->next)
		{
			printf("[%d] %s, ", infile->fd, infile->filename);
			infile = infile->next;
		}
		printf("\noutfile: ");
		while (table && outfile) // && table->outfile->next)
		{
			printf("[%d] %s, ", outfile->fd, outfile->filename);
			outfile = outfile->next;
		}
		printf("\ncmd: ");
		while (table->cmd[i])
			printf("%s ", table->cmd[i++]);
		printf("\nstatus: %d\n", table->status);
		table = table->next;
	}
	printf("---------------------------------------------\n");
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

	table = data->cmdtable;
	while (table)
	{
		//write(2, "what\n", 5);
		infile = file_get_last(table->infile);
		outfile = file_get_last(table->outfile);
		if (ft_check_fds(outfile, infile))
		{
			// ft_putstr_fd("\n\n\n\n", 2);
			// ft_putnbr_fd(outfile->fd, 2);
			// ft_putstr_fd(outfile->filename, 2);
			// ft_putstr_fd("\n\n\n\n", 2);
			dup2(infile->fd, 0);
			//display_cmdtable(data->cmdtable);
			ft_child(ft_arr_dup(table->cmd), env);
			dup2(outfile->fd, 1);
			close(outfile->fd);
			close(infile->fd);
			//dup2(4, 1);
		}
		table = table->next;
	}
	return (1);
}

int	ft_executor(t_data *data, char **env)
{
	(void)env;
	data->cmdtable = NULL;
	make_cmdtable(data);
	ft_putstr_fd("------pipex------", 2);
	ft_pipex(data, env);
	//close_files(data->cmdtable);
	//display_cmdtable(data->cmdtable);
	free_table(data->cmdtable);
	return (0);
}

//echo banana < in | ls < bingf | < bing
//<< EOF << banana >out1(nopermissions) ls -la <in <<yo <jfksj
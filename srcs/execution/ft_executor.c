/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:46:37 by yridgway          #+#    #+#             */
/*   Updated: 2023/01/03 20:36:59 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (table->cmd)
			printf("\n\tcmd: ");
		else
			printf("\n\tcmd: NULL");
		while (table->cmd && table->cmd[i])
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
	return (copy);
}

void	ft_check_fds(t_cmdtable *table)
{
	t_filelist	*infile;
	t_filelist	*outfile;

	while (table)
	{
		infile = file_get_last(table->infile);
		outfile = file_get_last(table->outfile);
		if (!infile || !outfile || (outfile->fd != -1 && infile->fd != -1))
		{
			table->status = 1;
			table = table->next;
			continue ;
		}
		else if (outfile->fd == -1 && infile->fd == -1)
		{
			if (outfile->order < infile->order)
				perror(outfile->filename);
			else
				perror(infile->filename);
		}
		else if (outfile->fd == -1)
			perror(outfile->filename);
		perror(infile->filename);
		table->status = 0;
		table = table->next;
	}
}

void	ft_close_pipes(t_data *data)
{
	if (data->open_pipe)
	{
		if (data->pipe[0] != -1)
			close(data->pipe[0]);
		if (data->pipe[1] != -1)
			close(data->pipe[1]);
	}
	data->open_pipe = 0;
}

void	ft_close_fds(t_data *data)
{
	t_filelist	*in;
	t_filelist	*out;
	t_cmdtable	*tab;

	tab = data->cmdtable;
	while (tab)//) && tab->infile && tab->outfile)
	{
		// printf("tab: %p\n", tab);
		// printf("tab->next: %p\n", tab->next);
		if (!tab || !tab->infile || !tab->outfile)
			break ;
		in = tab->infile;
		out = tab->outfile;
		while (in)
		{
			if (in->fd > 2)
				close(in->fd);
			in = in->next;
		}
		while (out)
		{
			if (out->fd > 2)
				close(out->fd);
			out = out->next;
		}
		if (tab)
			tab = tab->next;
	}
	ft_close_pipes(data);
}

int	ft_pipex(t_data *data)
{
	t_cmdtable	*table;

	table = data->cmdtable;
	if (!table)
		return (0);
	ft_check_fds(table);
	data->insave = dup(0);
	data->outsave = dup(1);
	while (table)
	{
		if (table->status)
			ft_pipe(data, table, ft_arr_dup(table->cmd));
		table = table->next;
		ft_close_pipes(data);
	}
	ft_close_fds(data);
	dup2(data->insave, 0);
	dup2(data->outsave, 1);
	close(data->insave);
	close(data->outsave);
	return (1);
}

int	ft_executor(t_data *data, char **env)
{
	(void)env;
	data->cmdtable = NULL;
	// print_list(data->cmd);
	if (make_cmdtable(data))
		return (1);
	// print_list(data->cmd);
	// ft_putstr_fd("\t------pipex------\n", 2);
	// if (data->cmdtable)
	// 	display_cmdtable(data->cmdtable);
	// ft_putstr_fd("\t------------------\n\n", 2);
	ft_pipex(data);
	//close_files(data->cmdtable);
	// if (data->cmdtable)
	// 	display_cmdtable(data->cmdtable);
	free_table(data->cmdtable);
	return (0);
}

//echo banana < in | ls < bingf | < bing
//<< EOF << banana >out1(nopermissions) ls -la <in <<yo <jfksj
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:46:37 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/04 21:38:16 by yridgway         ###   ########.fr       */
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
			printf("[%d] %s, ", \
			infile->fd, infile->filename);
			infile = infile->next;
		}
		printf("\noutfile: ");
		while (table && outfile) // && table->outfile->next)
		{
			printf("[%d] %s, ", \
			outfile->fd, outfile->filename);
			outfile = outfile->next;
		}
		printf("\ncmd: ");
		while (table->cmd[i])
			printf("%s ", table->cmd[i++]);
		printf("\n");
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
	i = -1;
	if (!arr)
		return (NULL);
	while (arr[count])
		count++;
	copy = malloc(sizeof(char *) * count + 1);
	while (++i < count)
		copy[i] = ft_strdup(arr[i]);
	copy[i] = NULL;
	ft_putstr_fd(copy[0], 2);
	return (copy);
}

// void	ft_pipex(t_data *data, char **env)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < 2)
// 	{
// 		//write(2, "what\n", 5);
// 		dup2(ft_infd(data, i), 0);
// 		//display_cmdtable(data->cmdtable);
// 		ft_child(ft_arr_dup(data->cmdtable->cmd), env);
// 		//dup2(4, 1);
// 	}
// }

int	ft_executor(t_data *data, char **env)
{
	(void)env;
	data->cmdtable = NULL;
	make_cmdtable(data);
	//display_cmdtable(data->cmdtable);
	//display_cmdtable(data->cmdtable);
	//ft_pipex(data, env);
	//close_files(data->cmdtable);
	display_cmdtable(data->cmdtable);
	free_table(data->cmdtable);
	// while(data->filelist)
	// {
	// 	ft_putstr_fd(data->filelist->filename, 2);
	// 	write(2, "\n", 1);
	// 	data->filelist = data->filelist->next;
	// }
	return (0);
}

//echo banana < in | ls < bingf | < bing
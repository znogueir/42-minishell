/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/02 19:23:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	display_cmdtable(t_cmdtable *table)
// {
// 	int			i;
// 	t_filelist	*infile;
// 	t_filelist	*outfile;

// 	while (table)
// 	{
// 		printf("\n");
// 		infile = table->infile;
// 		outfile = table->outfile;
// 		i = 0;
// 		printf("\tinfile: ");
// 		while (table && infile)
// 		{
// 			printf("[%d] %s, ", infile->fd, infile->filename);
// 			infile = infile->next;
// 		}
// 		printf("\n\toutfile: ");
// 		while (table && outfile)
// 		{
// 			printf("[%d] %s, ", outfile->fd, outfile->filename);
// 			outfile = outfile->next;
// 		}
// 		if (table->cmd)
// 			printf("\n\tcmd: ");
// 		else
// 			printf("\n\tcmd: NULL");
// 		while (table->cmd && table->cmd[i])
// 			printf("%s ", table->cmd[i++]);
// 		printf("\n\tstatus: %d\n", table->status);
// 		table = table->next;
// 		printf("\n");
// 	}
// }

void	convert_env(t_data *data, t_env *loc_env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = loc_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	data->char_env = ft_malloc(NULL, data, sizeof(char *) * (i + 1));
	i = 0;
	while (loc_env)
	{
		data->char_env[i++] = ft_strjoin(data, ft_strjoin(data, \
		ft_strdup(data, loc_env->name), "="), loc_env->content);
		loc_env = loc_env->next;
	}
	data->char_env[i] = NULL;
}

char	**ft_arr_dup(t_data *data, char **arr)
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
	copy = ft_malloc(NULL, data, sizeof(char *) * (count + 1));
	while (i < count)
	{
		copy[i] = ft_strdup(data, arr[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

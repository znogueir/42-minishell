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

int	ft_infd(t_data *data, int i)
{
	t_filelist *files;

	files = data->filelist;
	while (files && i > 0)
	{
		files = files->next;
		if (files && files->type == LESS)
			i--;
	}
	if (files)
		return(files->fd);
	return (0);
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
	copy = malloc(sizeof (char *) * count + 1);
	while (++i < count)
		copy[i] = ft_strdup(arr[i]);
	copy[i] = NULL;
	ft_putstr_fd(copy[0], 2);
	return (copy);
}

void	ft_pipex(t_data *data, char **env)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		//write(2, "what\n", 5);
		dup2(ft_infd(data, i), 0);
		//display_cmdtable(data->cmdtable);
		ft_child(ft_arr_dup(data->cmdtable->cmd), env);
		//dup2(4, 1);
	}
}

int	ft_executor(t_data *data, char **env)
{
	(void)env;
	data->cmdtable = NULL;
	make_cmdtable(data);
	//display_cmdtable(data->cmdtable);
	display_cmdtable(data->cmdtable);
	//open_redir_files(data, data->cmdtable);
	//display_cmdtable(data->cmdtable);
//	ft_pipex(data, env);
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
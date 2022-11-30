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

// void	ft_pipex(t_data *data)
// {
// 	while (++i < ac - 2)
// 	{
// 		dup2(infd, 0);
// 		ft_child(av[i], env);
// 		//dup2(outfd, 1);
// 	}
// }

int	ft_executor(t_data *data)
{
	make_cmdtable(data);
	display_cmdtable(data->cmdtable);
	//display_cmdtable(data->cmdtable);
	open_redir_files(data, data->cmdtable);
	display_cmdtable(data->cmdtable);
	//ft_pipex(data);
	// while(data->filelist)
	// {
	// 	ft_putstr_fd(data->filelist->filename, 2);
	// 	write(2, "\n", 1);
	// 	data->filelist = data->filelist->next;
	// }
	return (0);
}

//echo banana < in | ls < bingf | < bing
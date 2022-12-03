/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:53:01 by yridgway          #+#    #+#             */
/*   Updated: 2022/11/30 16:53:02 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	ft_error_opening(t_cmdtable *table, char *filename)
{
	perror(filename);
	while (table)
	{
		if (table->infd > 2)
			close(table->infd);
		if (table->outfd > 2)
			close(table->outfd);
		table = table->next;
	}
}

void	close_files(t_cmdtable *table)
{
	t_cmdtable	*beg;

	beg = table;
	while (table)
	{
		if (table->infd < 0)
			return (ft_error_opening(beg, table->infile));
		else if (table->outfd < 0)
			return (ft_error_opening(beg, table->outfile));
		else
			table = table->next;
	}
}

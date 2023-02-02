/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:38:18 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/02 18:58:53 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *extra)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	if (extra)
	{
		write(2, ": ", 2);
		ft_putstr_fd(extra, 2);
	}
	write(2, "\n", 1);
}

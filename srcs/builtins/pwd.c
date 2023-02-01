/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:23 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 20:21:17 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*cd;

	cd = NULL;
	cd = getcwd(cd, 0);
	if (cd == NULL)
		return (perror("pwd"), 1);
	printf("%s\n", cd);
	ft_free(cd);
	return (0);
}

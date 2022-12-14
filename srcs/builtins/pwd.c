/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:23 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/15 17:23:25 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cd;

	cd = NULL;
	cd = getcwd(cd, 100);
	if (cd == NULL)
		return (perror("pwd"), 1);
	ft_printf("%s\n", cd);
	free(cd);
	return (0);
}

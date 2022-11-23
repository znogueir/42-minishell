/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:15 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/15 17:23:17 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_data *data, char *name, char *content)
{
	(void)data;
	(void)content;
	// ft_envadd_back(&(data->loc_env), ft_envnew(name, content));
	ft_printf("test cmd : export $%s\n", name);
	return (0);
}

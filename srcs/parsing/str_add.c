/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:29:05 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/30 18:32:36 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_stradd_char(t_data *data, char *str, char c)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_malloc(data, sizeof(char) * (ft_strlen(str) + 2));
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	// free(str);
	return (new_str);
}

char	*ft_add_excode(t_data *data, char *str, int *p_i)
{
	int		i;
	int		j;
	char	*new_str;
	char	*excode;

	i = 0;
	excode = ft_itoa(g_exit);
	new_str = ft_malloc(data, sizeof(char) * \
	(ft_strlen(str) + ft_strlen(excode) + 1));
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	j = 0;
	while (excode[j] != '\0')
		new_str[i++] = excode[j++];
	new_str[i] = '\0';
	// free(str);
	// free(excode);
	(*p_i) += 2;
	return (new_str);
}

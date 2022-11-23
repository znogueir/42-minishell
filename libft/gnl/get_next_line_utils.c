/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:10:44 by znogueir          #+#    #+#             */
/*   Updated: 2022/06/02 20:53:49 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cut_line(char *line, char *save)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] != '\n')
		i++;
	if (line && line[i] == '\n')
		i++;
	save = ft_substr(line, i, ft_strlen(line + i));
	if (line && line[i])
		line[i] = '\0';
	return (save);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[len] = '\0';
	free(s1);
	return (result);
}

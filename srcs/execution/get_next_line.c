/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:40:31 by yridgway          #+#    #+#             */
/*   Updated: 2022/10/27 17:03:23 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_hasnl(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_cutcopy(char *line, char *save)
{
	int		i;
	char	*new;

	i = 0;
	while (save && save[i] != '\n' && save[i])
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	new = ft_strdup(save + i);
	free(save);
	return (new);
}

char	*ft_makeline(char *save)
{
	int		i;
	char	*new;

	i = 0;
	while (save && save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
		i++;
	new = (char *)malloc((i + 1) * sizeof (char));
	if (!new)
		return (NULL);
	return (new);
}

char	*get_next_line(int fd, int a)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*save;
	char			*line;
	int				i;

	i = BUFFER_SIZE;
	while (i == BUFFER_SIZE && !ft_hasnl(save))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
			return (NULL);
		buf[i] = '\0';
		save = ft_strjoin(save, buf);
	}
	if (!save || (i < BUFFER_SIZE && !save[0]))
	{
		if (a)
			free(save);
		return (NULL);
	}
	line = ft_makeline(save);
	save = ft_cutcopy(line, save);
	return (line);
}

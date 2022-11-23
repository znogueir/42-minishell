/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:26:36 by znogueir          #+#    #+#             */
/*   Updated: 2022/06/07 20:26:39 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *line)
{
	int		ret;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ret = 1;
	while (ret && ft_strchr(line, '\n') == 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buffer[ret] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	if (save[fd])
		line = save[fd];
	line = read_line(fd, line);
	if (!line)
	{
		free(save[fd]);
		return (NULL);
	}
	save[fd] = cut_line(line, save[fd]);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int	f;
	char	*line;

	f = open("big_line_with_nl", O_RDONLY);
	line = get_next_line(f);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(f);
	}
	close(f);
	return (0);
}*/
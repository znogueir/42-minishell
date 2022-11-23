/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:23:25 by znogueir          #+#    #+#             */
/*   Updated: 2022/05/19 19:13:59 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	if (save)
		line = save;
	line = read_line(fd, line);
	if (!line)
	{
		free(save);
		return (NULL);
	}
	save = cut_line(line, save);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	(void)ac;
	int	f;
	char	*line;

	f = open(av[1], O_RDONLY);
	line = get_next_line(f);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(f);
	}
	line = get_next_line(f);
	printf("%s", line);
	free(line);
	close(f);
	return (0);
}
*/
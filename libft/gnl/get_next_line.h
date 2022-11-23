/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:11:32 by znogueir          #+#    #+#             */
/*   Updated: 2022/06/02 20:54:18 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft.h"

# define BUFFER_SIZE 1

char	*cut_line(char *line, char *save);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:26:45 by znogueir          #+#    #+#             */
/*   Updated: 2022/06/07 20:26:46 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "../libft.h"

# define BUFFER_SIZE 1

char	*cut_line(char *line, char *save);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
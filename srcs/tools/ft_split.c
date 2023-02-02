/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:47:16 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/02 19:22:15 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wlen(char const *substr, char *sep)
{
	int	i;

	i = 0;
	while (substr[i] && !ft_strchr(sep, substr[i]))
		i++;
	return (i);
}

int	ft_wcount(char const *s, char *sep)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(sep, s[i]))
			i++;
		if (s[i])
			wcount++;
		while (s[i] && !ft_strchr(sep, s[i]))
			i++;
	}
	return (wcount);
}

char	*ft_word(t_data *data, char const *substr, char *sep)
{
	int		i;
	char	*word;

	word = ft_malloc(NULL, data, sizeof(char) * (ft_wlen(substr, sep) + 1));
	if (!word)
		return (0);
	i = 0;
	while (i < ft_wlen(substr, sep))
	{
		word[i] = substr[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(t_data *data, char const *s, char *sep)
{
	int		i;
	int		j;
	int		wcount;
	char	**result;

	wcount = ft_wcount(s, sep);
	result = (char **)ft_malloc(NULL, data, sizeof(char *) * (wcount + 1));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(sep, s[i]))
			i++;
		if (s[i])
		{
			result[j] = ft_word(data, (s + i), sep);
			j++;
		}
		while (s[i] && !ft_strchr(sep, s[i]))
			i++;
	}
	result[j] = 0;
	return (result);
}

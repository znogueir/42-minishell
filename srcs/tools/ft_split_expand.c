/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:50:22 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/09 04:18:15 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len(char const *s, char c)
{
	int	k;
	int	len;
	int	quote;

	quote = 1;
	k = 0;
	len = 0;
	while (s[k] && (s[k] != c || quote < 0))
	{
		if (s[k] == '\"')
			quote *= -1;
		len++;
		k++;
	}
	return (len);
}

char	**ft_makearr(t_data *data, char const *s, char c)
{
	char	**arr;
	int		i;
	int		count;
	int		quote;

	i = 0;
	count = 0;
	quote = 1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && (s[i] != c || quote < 0))
		{
			if (s[i] == '\"')
				quote *= -1;
			i++;
		}
	}
	arr = ft_malloc(NULL, data, (count + 1) * sizeof (char *));
	return (arr);
}

char	*ft_putword(t_data *data, char const *s, char c)
{
	char	*word;
	int		k;
	int		quote;

	k = 0;
	quote = 1;
	word = ft_malloc(NULL, data, (ft_len(s, c) + 1) * sizeof (char));
	if (!word)
		return (NULL);
	while (s[k] && (s[k] != c || quote < 0))
	{
		if (s[k] == '\"')
			quote *= -1;
		word[k] = s[k];
		k++;
	}
	word[k] = '\0';
	return (word);
}

char	**ft_split_expand(t_data *data, char const *s, char c)
{
	int		i;
	int		k;
	int		quote;
	char	**arr;

	arr = ft_makearr(data, s, c);
	if (!arr)
		return (NULL);
	i = 0;
	k = 0;
	quote = 1;
	while (s[k])
	{
		while (s[k] && s[k] == c)
			k++;
		if (s[k])
			arr[i++] = ft_putword(data, (s + k), c);
		while (s[k] && (s[k] != c || quote < 0))
		{
			if (s[k++] == '\"')
				quote *= -1;
		}
	}
	arr[i] = 0;
	return (arr);
}

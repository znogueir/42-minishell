/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_matching_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:01:37 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/03 20:01:43 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pattern_nbr(t_data *data, char *pattern)
{
	int		size;
	char	*wc_bin;

	size = 0;
	wc_bin = data->wc.wc_bin;
	while (*pattern)
	{
		while (*pattern == '*' && *wc_bin == '1')
		{
			pattern++;
			wc_bin++;
		}
		if (!*pattern)
			return (size);
		size++;
		while (*pattern)
		{
			if (*pattern == '*' && *wc_bin == '1')
				break ;
			else if (*pattern == '*' && *wc_bin == '0')
				wc_bin++;
			pattern++;
		}
	}
	return (size);
}

void	mini_fill(t_data *data, char ***strs_to_find, int *i, int *j)
{
	while (*data->wc.pattern)
	{
		if (!data->wc.pattern[*j] || (data->wc.pattern[*j] == '*' && \
		*data->wc.wc_bin == '1'))
		{
			(*strs_to_find)[(*i)++] = ft_substr(data, data->wc.pattern, 0, *j);
			data->wc.pattern += *j;
			*j = 0;
			break ;
		}
		else if (data->wc.pattern[*j] && data->wc.pattern[*j] == '*' && \
		*data->wc.wc_bin == '0')
			data->wc.wc_bin++;
		(*j)++;
	}
}

char	**fill_strs(t_data *data, int size)
{
	int		i;
	int		j;
	char	**strs_to_find;

	i = 0;
	j = 0;
	strs_to_find = ft_malloc(NULL, data, sizeof(char *) * (size + 1));
	while (data->wc.pattern[j])
	{
		while (*data->wc.pattern == '*' && *data->wc.wc_bin == '1')
		{
			data->wc.pattern++;
			data->wc.wc_bin++;
		}
		mini_fill(data, &strs_to_find, &i, &j);
	}
	strs_to_find[i] = NULL;
	return (strs_to_find);
}

int	str_match(t_data *data, char **strs_to_find, int size)
{
	int	i;
	int	len;
	int	fn_len;
	int	strs_len;

	i = 0;
	while (strs_to_find && strs_to_find[i])
	{
		strs_len = ft_strlen(strs_to_find[i]);
		fn_len = ft_strlen(data->wc.file_name);
		if (data->wc.begin && i == 0)
			len = ft_strlen(strs_to_find[i]);
		else if (data->wc.end && i == size - 1)
		{
			data->wc.file_name += (fn_len - strs_len * (strs_len < fn_len));
			len = ft_strlen(strs_to_find[i]);
		}
		else
			len = ft_strlen(data->wc.file_name);
		if (!ft_strnstr(data->wc.file_name, strs_to_find[i], len))
			return (0);
		data->wc.file_name = ft_strnstr(data->wc.file_name, \
		strs_to_find[i++], len) + strs_len;
	}
	return (1);
}

int	check_filename3(t_data *data, char *pattern)
{
	int		ret;
	int		size;
	char	**strs_to_find;

	data->wc.pattern = pattern;
	size = get_pattern_nbr(data, pattern);
	if (!size)
		return (1);
	data->wc.begin = (pattern[0] != '*' || (pattern[0] == '*' && \
	data->wc.wc_bin[0] == '0'));
	data->wc.end = (pattern[ft_strlen(pattern) - 1] != '*' || \
	(pattern[ft_strlen(pattern) - 1] == '*' && \
	data->wc.wc_bin[ft_strlen(data->wc.wc_bin) - 1] == '0'));
	data->wc.wc_bin_head = data->wc.wc_bin;
	strs_to_find = fill_strs(data, size);
	ret = str_match(data, strs_to_find, size);
	data->wc.wc_bin = data->wc.wc_bin_head;
	return (free_split(strs_to_find), ret);
}

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

int	get_size(t_data *data, char *pattern)
{
	int		size;
	char	*wc_bin;

	size = 0;
	wc_bin = data->wc->wc_bin;
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
			if (*pattern == '*' && *wc_bin)
				break ;
			else if (*pattern == '*' && !*wc_bin)
				wc_bin++;
			pattern++;
		}
	}
	return (size);
}

// void	mini_fill(t_data *data, char **pattern, int *i, int *j)
// {
// 	while (**pattern)
// 	{
// 		if (!*pattern[*j] || ((*pattern)[*j] == '*' && *data->wc->wc_bin))
// 		{
// 			data->wc->strs_to_find[(*i)++] = ft_substr(data, *pattern, 0, *j);
// 			*pattern += *j;
// 			*j = 0;
// 			break ;
// 		}
// 		else if ((*pattern)[*j] && (*pattern)[*j] == '*' && !*data->wc->wc_bin)
// 			data->wc->wc_bin++;
// 		(*j)++;
// 	}
// }

char	**fill_strs(t_data *data, char *pattern, int size)
{
	int		i;
	int		j;
	char	**strs_to_find;

	i = 0;
	j = 0;
	strs_to_find = ft_malloc(NULL, data, sizeof(char *) * (size + 1));
	while (pattern[j])
	{
		while (*pattern == '*' && *data->wc->wc_bin == '1')
		{
			pattern++;
			data->wc->wc_bin++;
		}
		while (*pattern)
		{
			if (!pattern[j] || (pattern[j] == '*' && *data->wc->wc_bin))
			{
				strs_to_find[i++] = ft_substr(data, pattern, 0, j);
				pattern += j;
				j = 0;
				break ;
			}
			else if (pattern[j] && pattern[j] == '*' && !*data->wc->wc_bin)
				data->wc->wc_bin++;
			j++;
		}
		// mini_fill(data, &pattern, &i, &j);
	}
	strs_to_find[i] = NULL;
	return (strs_to_find);
}

int	str_match(t_data *data, char **strs_to_find, int size)
{
	int	i;
	int	len;

	i = 0;
	while (strs_to_find[i])
	{
		if (data->wc->begin && i == 0)
			len = ft_strlen(strs_to_find[i]);
		else if (data->wc->end && i == size - 1)
		{
			data->wc->file_name += (ft_strlen(data->wc->file_name) - \
			ft_strlen(strs_to_find[i]));
			len = ft_strlen(strs_to_find[i]);
		}
		else
			len = ft_strlen(data->wc->file_name);
		if (!ft_strnstr(data->wc->file_name, strs_to_find[i], len))
			return (0);
		data->wc->file_name = ft_strnstr(data->wc->file_name, strs_to_find[i], \
		len) + ft_strlen(strs_to_find[i]);
		i++;
	}
	return (1);
}

int	check_filename3(t_data *data, char *pattern, int start)
{
	int		size;
	char	**strs_to_find;

	(void)start;
	size = get_size(data, pattern);
	data->wc->begin = (pattern[0] != '*' || (pattern[0] == '*' && \
	!data->wc->wc_bin[0]));
	data->wc->end = (pattern[ft_strlen(pattern) - 1] != '*' || \
	(pattern[ft_strlen(pattern) - 1] == '*' && \
	!data->wc->wc_bin[ft_strlen(data->wc->wc_bin) - 1]));
	init_wildcards(data, pattern);
	strs_to_find = fill_strs(data, pattern, size);
	// free_split(strs_to_find);
	data->wc->wc_bin = data->wc->wc_bin_head;
	return (str_match(data, strs_to_find, size));
}

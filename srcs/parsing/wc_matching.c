/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_matching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:10:29 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/02 20:34:36 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	consume_stars(t_data *data, char **pattern)
{
	while (**pattern == '*' && *data->wc->wc_bin == '1')
	{
		(*pattern)++;
		(data->wc->wc_bin)++;
	}
	if (!**pattern)
	{
		data->wc->wc_bin = data->wc->wc_bin_head;
		return (1);
	}
	data->wc->pattern_save = *pattern;
	data->wc->wc_bin_save = data->wc->wc_bin;
	return (0);
}

int	not_matching_1(t_data *data, char **pattern, int *start)
{
	if (*start || !*data->wc->file_name)
	{
		data->wc->wc_bin = data->wc->wc_bin_head;
		return (0);
	}
	*start = 0;
	data->wc->file_name++;
	if (**pattern != data->wc->pattern_save[0])
		data->wc->file_name -= data->wc->streak;
	data->wc->streak = 0;
	*pattern = data->wc->pattern_save;
	data->wc->wc_bin = data->wc->wc_bin_save;
	return (1);
}

int	not_matching_2(t_data *data, char **pattern, int *start)
{
	if (!*data->wc->file_name)
	{
		data->wc->wc_bin = data->wc->wc_bin_head;
		return (0);
	}
	*start = 0;
	data->wc->file_name++;
	if (**pattern != data->wc->pattern_save[0])
		data->wc->file_name -= data->wc->streak;
	data->wc->streak = 0;
	*pattern = data->wc->pattern_save;
	data->wc->wc_bin = data->wc->wc_bin_save;
	return (1);
}

void	finish_checking(t_data *data, char **pattern, int *start)
{
	if (**pattern == '*' && *data->wc->wc_bin == '0')
		data->wc->wc_bin++;
	(*pattern)++;
	data->wc->streak++;
	data->wc->file_name++;
	*start = 0;
	if (!**pattern && *data->wc->file_name)
	{
		data->wc->wc_bin = data->wc->wc_bin_save;
		*pattern = data->wc->pattern_save;
		printf("[%s]\n", data->wc->pattern_save);
		data->wc->streak = 0;
	}
}

int	check_filename2(t_data *data, char *pattern, int start)
{
	init_wildcards(data, pattern);
	while (*pattern)
	{
		if (*pattern == '*' && *data->wc->wc_bin == '1')
		{
			if (consume_stars(data, &pattern))
				return (1);
		}
		else if (*pattern != *data->wc->file_name)
		{
			if (!not_matching_1(data, &pattern, &start))
				return (0);
			continue ;
		}
		if (*pattern != *data->wc->file_name)
		{
			if (!not_matching_2(data, &pattern, &start))
				return (0);
			continue ;
		}
		finish_checking(data, &pattern, &start);
	}
	data->wc->wc_bin = data->wc->wc_bin_head;
	return (!*pattern && !*data->wc->file_name);
}

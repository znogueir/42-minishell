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
	{
	data->wc->file_name -= data->wc->streak;
	}
	// printf("not matching 1 before - streak : [%d]\n", data->wc->streak);
	// printf("not matching 1 before - pattern : [%s]\n", *pattern);
	// printf("not matching 1 before - file_name : [%s]\n", data->wc->file_name);
	data->wc->streak = 0;
	*pattern = data->wc->pattern_save;
	data->wc->wc_bin = data->wc->wc_bin_save;
	// printf("not matching 1 after - streak : [%d]\n", data->wc->streak);
	// printf("not matching 1 after - pattern : [%s]\n", *pattern);
	// printf("not matching 1 after - file_name : [%s]\n", data->wc->file_name);
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
	{
	data->wc->file_name -= data->wc->streak;
	}
	// printf("not matching 2 before - streak : [%d]\n", data->wc->streak);
	// printf("not matching 2 before - pattern : [%s]\n", *pattern);
	// printf("not matching 2 before - file_name : [%s]\n", data->wc->file_name);
	data->wc->streak = 0;
	*pattern = data->wc->pattern_save;
	data->wc->wc_bin = data->wc->wc_bin_save;
	// printf("not matching 2 after - streak : [%d]\n", data->wc->streak);
	// printf("not matching 2 after - pattern : [%s]\n", *pattern);
	// printf("not matching 2 after - file_name : [%s]\n", data->wc->file_name);
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
	// printf("finish outside if - streak : [%d]\n", data->wc->streak);
	// printf("finish outside if - pattern : [%s]\n", *pattern);
	// printf("finish outside if - file_name : [%s]\n", data->wc->file_name);
	if (!**pattern && *data->wc->file_name)
	{
		data->wc->wc_bin = data->wc->wc_bin_save;
		// printf("finish before - streak : [%d]\n", data->wc->streak);
		// printf("finish before - pattern : [%s]\n", *pattern);
		// printf("finish before - file_name : [%s]\n", data->wc->file_name);
		// if (**pattern != data->wc->pattern_save[0])
		// {
		// 	data->wc->file_name -= data->wc->streak;
		// }
		*pattern = data->wc->pattern_save;
		data->wc->streak = 0;
	// 	printf("finish after - streak : [%d]\n", data->wc->streak);
	// 	printf("finish after - pattern : [%s]\n", *pattern);
	// 	printf("finish after - file_name : [%s]\n", data->wc->file_name);
	// }
	// else if (**pattern && !*data->wc->file_name && !*end)
	// {
	// 	data->wc->file_name -= data->wc->streak;
	// 	*end = 1;
	}
}

// int last_check(char *pattern)
// {
// 	int	i;

// 	i = 0;
// 	while (*pattern)
// 		pattern++;
// 	while (*pattern-- != '*')
// 		i++;
// 	return (i);
// }

int	check_filename2(t_data *data, char *pattern, int start)
{
	// int	end;

	// end = 0;
	init_wildcards(data, pattern);
	while (*pattern)
	{
		if (*pattern == '*' && *data->wc->wc_bin == '1')
		{
			if (consume_stars(data, &pattern))
				return (printf("consume stars exit\n\n"), 1);
		}
		else if (*pattern != *data->wc->file_name)
		{
			if (!not_matching_1(data, &pattern, &start))
				return (printf("not matching 1 \n\n"), 0);
			continue ;
		}
		if (*pattern != *data->wc->file_name)
		{
			if (!not_matching_2(data, &pattern, &start))
				return (printf("not matching 2 \n\n"), 0);
			continue ;
		}
		finish_checking(data, &pattern, &start);
	}
	data->wc->wc_bin = data->wc->wc_bin_head;
	return (printf("result : %d\n\n", (!*pattern && !*data->wc->file_name)), \
	(!*pattern && !*data->wc->file_name));
}

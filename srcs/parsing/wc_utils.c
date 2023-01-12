/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:04:15 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/05 22:04:16 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdline	*get_last_cmd(t_cmdline *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}

t_cmdline	*finish_wc(t_data *data, t_cmdline *matching, t_cmdline *p_cmd)
{
	t_cmdline	*tmp;
	t_cmdline	*ret;

	ret = p_cmd;
	if (matching)
	{
		tmp = p_cmd->next;
		p_cmd->next = matching->next;
		free(p_cmd->content);
		p_cmd->content = ft_strdup(matching->content);
		if (matching->next)
		{
			ret = get_last_cmd(matching);
			ret->next = tmp;
		}
		free(matching->content);
		free(matching);
	}
	// free(data->wildcards);
	// data->wildcards = NULL;
	free(data->wc->wc_bin);
	data->wc->wc_bin = NULL;
	return (ret);
}

int	is_dir(char *name)
{
	int				type;
	DIR				*cwd;
	struct dirent	*dir_content;

	cwd = opendir(".");
	if (!cwd)
		return (-1);
	dir_content = readdir(cwd);
	while (dir_content)
	{
		if (!better_strncmp(name, dir_content->d_name, ft_strlen(name)))
		{
			type = dir_content->d_type;
			return (closedir(cwd), type == 4);
		}
		dir_content = readdir(cwd);
	}
	closedir(cwd);
	return (0);
}

int	is_wildcard(t_data *data)
{
	int	i;

	i = 0;
	while (data->wc->wc_bin && data->wc->wc_bin[i])
	{
		if (data->wc->wc_bin[i] == '1')
			return (1);
		i++;
	}
	free(data->wc->wc_bin);
	data->wc->wc_bin = NULL;
	return (0);
}

int	consume_stars(char **pattern, char **wc)
{
	while (**pattern == '*' && **wc == '1')
	{
		(*pattern)++;
		(*wc)++;
	}
	if (!**pattern)
	{
		return (1);
	}
	return (0);
}

int	check_filename(char *file_name, char *pattern, char *wc, int start)
{
	int		i;
	char	*save;
	char	*wc_save;

	i = 0;
	save = pattern;
	wc_save = wc;
	while (*pattern)
	{
		if (*pattern == '*' && *wc == '1')
		{
			if (consume_stars(&pattern, &wc))
				return (1);
			save = pattern;
			wc_save = wc;
		}
		else if (*pattern != *file_name)
		{
			if (start || !*file_name)
				return (0);
			start = 0;
				file_name++;
			if (*pattern != save[0])
				file_name -= i;
			pattern = save;
			wc = wc_save;
			i = 0;
			continue ;
		}
		if (*pattern != *file_name)
		{
			if (!*file_name)
				return (0);
			start = 0;
				file_name++;
			if (*pattern != save[0])
				file_name -= i;
			pattern = save;
			wc = wc_save;
			i = 0;
			continue ;
		}
		if (*pattern == '*' && *wc == '0')
			wc++;
		pattern++;
		i++;
		file_name++;
		start = 0;
		if (!*pattern && *file_name)
		{
			wc = wc_save;
			pattern = save;
			i = 0;
		}
	}
	return (!*pattern && !*file_name);
}


// int	not_matching_1(t_data *data, char **pattern, char **wc, int *start)
// {
// 	if (*start || !**file_name)
// 		return (0);
// 	*start = 0;
// 		(*file_name)++;
// 	if (**pattern != save[0])
// 		file_name -= i;
// 	pattern = save;
// 	wc = wc_save;
// 	i = 0;
// }

// int	not_matching_2(t_data *data, char **pattern, char **wc, int *start)
// {
// 	if (*start || !data->wc->file_name)
// 		return (0);
// 	*start = 0;
// 		data->wc->file_name++;
// 	if (*pattern != save[0])
// 		file_name -= data->wc->streak;
// 	pattern = save;
// 	wc = wc_save;
// 	data->wc->streak = 0;
// 	return (1);
// }

int	check_filename2(t_data *data, char *file_name, char *pattern, int start)
{
	// int		i;
	char	*save;
	char	*wc;
	char	*wc_save;

	data->wc->streak = 0;
	save = pattern;
	wc = data->wc->wc_bin;
	wc_save = data->wc->wc_bin;
	while (*pattern)
	{
		if (*pattern == '*' && *data->wc->wc_bin == '1')
		{
			if (consume_stars(&pattern, &data->wc->wc_bin))
			{
				data->wc->wc_bin = wc;
				return (1);
			}
			save = pattern;
			wc_save = data->wc->wc_bin;
		}
		else if (*pattern != *file_name)
		{
			if (start || !*file_name)
			{
				data->wc->wc_bin = wc;
				return (0);
			}
			start = 0;
				file_name++;
			if (*pattern != save[0])
				file_name -= data->wc->streak;
			pattern = save;
			data->wc->wc_bin = wc_save;
			data->wc->streak = 0;
			continue ;
		}
		if (*pattern != *file_name)
		{
			if (!*file_name)
			{
				data->wc->wc_bin = wc;
				return (0);
			}
			start = 0;
				file_name++;
			if (*pattern != save[0])
				file_name -= data->wc->streak;
			pattern = save;
			data->wc->wc_bin = wc_save;
			data->wc->streak = 0;
			continue ;
		}
		if (*pattern == '*' && *data->wc->wc_bin == '0')
			data->wc->wc_bin++;
		pattern++;
		data->wc->streak++;
		file_name++;
		start = 0;
		if (!*pattern && *file_name)
		{
			data->wc->wc_bin = wc_save;
			pattern = save;
			data->wc->streak = 0;
		}
	}
	// ft_printf("check filename wc : %s\n", wc);
	data->wc->wc_bin = wc;
	return (!*pattern && !*file_name);
}

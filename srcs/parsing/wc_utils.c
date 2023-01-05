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

void	finish_wc(t_data *data, char **str, char *new_str)
{
	char	*tmp;

	tmp = NULL;
	if (new_str)
	{
		free(*str);
		*str = NULL;
		tmp = new_str;
		*str = ft_strtrim(tmp, " ");
		free(new_str);
	}
	free(data->wildcards);
	data->wildcards = NULL;
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
	while (data->wildcards && data->wildcards[i])
	{
		if (data->wildcards[i] == '1')
			return (1);
		i++;
	}
	free(data->wildcards);
	data->wildcards = NULL;
	return (0);
}

int	check_filename(char *file_name, char *str, char *wc)
{
	if (*str == '*' && *wc == '1')
	{
		while (*str == '*' && *wc == '1')
		{
			str++;
			wc++;
		}
		if (!*str || *str == '/')
			return (1);
		while (*file_name && *str != *file_name)
			file_name++;
		if (!*file_name)
			return (0);
	}
	while (*str && *str != '/' && *file_name)
	{
		if (*str == '*')
		{
			if (*wc == '1')
				return (check_filename(file_name, str, wc));
			else
				wc++;
		}
		if (*str != *file_name)
			return (0);
		str++;
		file_name++;
	}
	if (!*file_name)
		return (1);
	return (0);
}

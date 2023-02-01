/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_filenames.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:00:34 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 20:38:38 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nbrof_files(void)
{
	int		count;
	DIR		*cwd;

	cwd = opendir(".");
	if (!cwd)
		return (-1);
	count = 0;
	while (readdir(cwd))
		count++;
	closedir(cwd);
	return (count);
}

void	ft_strswap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**alpha_sort(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[j + 1])
		{
			if (ft_alphacmp(str[j], str[j + 1]) < 0)
				ft_strswap(&str[j], &str[j + 1]);
			j++;
		}
		i++;
	}
	return (str);
}

char	**fill_names(t_data *data, DIR *cwd, struct dirent *dir_content, char **file_names)
{
	int	i;

	i = 0;
	dir_content = readdir(cwd);
	while (dir_content)
	{
		file_names[i] = ft_strdup(data, dir_content->d_name);
		dir_content = readdir(cwd);
		i++;
	}
	file_names[i] = NULL;
	closedir(cwd);
	return (file_names);
}

char	**get_file_names(t_data *data)
{
	int				nbr_of_files;
	DIR				*cwd;
	char			**file_names;
	struct dirent	*dir_content;

	nbr_of_files = get_nbrof_files();
	if (nbr_of_files == -1)
		return (NULL);
	file_names = ft_malloc(NULL, data, sizeof(char *) * (nbr_of_files + 1));
	cwd = opendir(".");
	if (!cwd)
		return (NULL);
	dir_content = NULL;
	file_names = fill_names(data, cwd, dir_content, file_names);
	return (alpha_sort(file_names));
}

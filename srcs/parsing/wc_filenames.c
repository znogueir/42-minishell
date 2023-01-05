/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_filenames.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:00:34 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/05 22:00:38 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nbrof_files(void)
{
	int		count;
	DIR		*cwd;

	cwd = opendir(".");
	if (!cwd)
		return (0);
	count = 0;
	while (readdir(cwd))
		count++;
	closedir(cwd);
	// ft_printf("%d\n", count);
	return (count);
}

void	ft_strswap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	alpha_sort(char **str)
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
		// print_names(str);
		i++;
	}
}

char	**get_file_names(void)
{
	int				nbr_of_files;
	int				i;
	DIR				*cwd;
	char			**file_names;
	struct dirent	*dir_content;

	nbr_of_files = get_nbrof_files();
	if (!nbr_of_files)
		return (NULL);
	file_names = malloc(sizeof(char *) * (nbr_of_files + 1));
	//protect malloc;
	cwd = opendir(".");
	if (!cwd)
		return (0);
	i = 0;
	dir_content = readdir(cwd);
	while (dir_content)
	{
		file_names[i] = ft_strdup(dir_content->d_name);
		dir_content = readdir(cwd);
		i++;
	}
	file_names[i] = NULL;
	closedir(cwd);
	alpha_sort(file_names);
	// print_names(file_names);
	return (file_names);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:23:06 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_var(t_data *data, char *new_word, char *str)
{
	int		size;
	char	*search_for;
	t_env	*p_env;

	size = 0;
	p_env = data->loc_env;
	while (is_alphanum(str[size]) || str[size] == '_')
		size++;
	search_for = ft_substr(str, 0, size);
	while (p_env && better_strncmp(p_env->name, search_for, size))
		p_env = p_env->next;
	if (p_env)
		new_word = ft_strjoin(new_word, p_env->content);
	free(search_for);
	return (new_word);
}

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

void	print_names(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_printf("%s\n", strs[i]);
		i++;
	}
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
	print_names(file_names);
	return (file_names);
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

void	expand_wc(t_data *data, char **str)
{
	int				i;
	char			*new_str;
	char			**file_names;

	if (!is_wildcard(data))
		return ;
	i = 0;
	new_str = NULL;
	file_names = get_file_names();
	while (file_names[i])
	{
		while (file_names[i] && (*str)[0] != '.' && file_names[i][0] == '.')
			free(file_names[i++]);
		while (file_names[i] && (*str)[ft_strlen(*str) - 1] == '/' && \
		!is_dir(file_names[i]))
			free(file_names[i++]);
		if (file_names[i] && check_filename(file_names[i], *str, \
		data->wildcards))
		{
			file_names[i] = ft_stradd_char(file_names[i], ' ');
			new_str = ft_strjoin(new_str, file_names[i]);
		}
		free(file_names[i++]);
	}
	free(file_names);
	finish_wc(data, str, new_str);
}

char	small_expand(t_data *data, char **new_word, char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '$' && str[*i + 1] == '?')
			*new_word = ft_add_excode(*new_word, i);
		else if (str[*i] == '$' && (str[*i + 1] == 34 || str[*i + 1] == 39))
			(*i)++;
		else if (str[*i] == '$' && (is_alphanum(str[*i + 1]) || \
		str[*i + 1] == '_'))
		{
			(*i)++;
			*new_word = replace_var(data, *new_word, str + *i);
			while (is_alphanum(str[*i]) || str[*i] == '_')
				(*i)++;
		}
		else if (str[*i] == 34 || str[*i] == 39)
			return (str[(*i)++]);
		else
		{
			if (str[*i] == '*')
				data->wildcards = ft_stradd_char(data->wildcards, '1');
			*new_word = ft_stradd_char(*new_word, str[(*i)++]);
		}
	}
	return (0);
}

char	*big_expand(t_data *data, char *new_word, char *str)
{
	int		i;
	char	end;

	i = 0;
	if (!str)
		return (NULL);
	end = small_expand(data, &new_word, str, &i);
	while (str[i] && str[i] != end)
	{
		if (str[i] == '$' && str[i + 1] == '?' && end == 34)
			new_word = ft_add_excode(new_word, &i);
		else if (str[i] == '$' && (is_alphanum(str[i + 1]) || \
		str[i + 1] == '_') && end == 34)
		{
			i++;
			new_word = replace_var(data, new_word, str + i);
			while (is_alphanum(str[i]) || str[i] == '_')
				i++;
		}
		else
		{
			if (str[i] == '*')
				data->wildcards = ft_stradd_char(data->wildcards, '0');
			new_word = ft_stradd_char(new_word, str[i++]);
		}
	}
	if (!str[i])
		return (new_word);
	return (big_expand(data, new_word, str + i + 1));
}

int	ft_expander(t_data *data)
{
	char		*new_word;
	t_cmdline	*p_cmd;

	p_cmd = data->cmd;
	while (p_cmd)
	{
		if (p_cmd->type == WORD)
		{
			new_word = NULL;
			if (!better_strncmp(p_cmd->content, "\"\"", 2) || \
			!better_strncmp(p_cmd->content, "\'\'", 2))
			{
				free(p_cmd->content);
				p_cmd->content = ft_strdup("");
			}
			else
			{
				new_word = big_expand(data, new_word, p_cmd->content);
				free(p_cmd->content);
				p_cmd->content = new_word;
				expand_wc(data, &p_cmd->content);
			}
		}
		p_cmd = p_cmd->next;
	}
	return (0);
}

// add a char* in every block that contains as many bytes as the number of '*',
// and for each 1 -> expand the '*' and for each 0 -> treat it as a normal char.
// 0 means it was in quotes.
// so in small_expand for each star -> add 1;
// and in big_expand for each star -> add 0;
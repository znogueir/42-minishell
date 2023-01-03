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

void	expand_wc(t_data *data, char *str)
{
	DIR				*cwd;
	struct dirent	*dir_content;

	(void)str;
	cwd = opendir(".");
	ft_printf("%s\n", data->wildcards);
	dir_content = readdir(cwd);
	while (dir_content)
	{
		ft_printf("%s\n", dir_content->d_name);
		dir_content = readdir(cwd);
	}
	free(str);
	str = NULL;
	str = ft_strdup("bla");
	free(data->wildcards);
	data->wildcards = NULL;
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
				expand_wc(data, p_cmd->content);
			}
		}
		p_cmd = p_cmd->next;
	}
	print_list(data->cmd);
	return (0);
}

// add a char* in every block that contains as many bytes as the number of '*',
// and for each 1 -> expand the '*' and for each 0 -> treat it as a normal char.
// 0 means it was in quotes.
// so in small_expand for each star -> add 1;
// and in big_expand for each star -> add 0;
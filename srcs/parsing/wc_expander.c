/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:23:06 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/27 14:55:37 by ionorb           ###   ########.fr       */
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

// void	print_names(char **strs)
// {
// 	int	i;

// 	i = 0;
// 	while (strs[i])
// 	{
// 		ft_printf("%s\n", strs[i]);
// 		i++;
// 	}
// }

t_cmdline	*expand_wc(t_data *data, char **str, t_cmdline *p_cmd)
{
	int				i;
	t_cmdline		*matching;
	char			**file_names;

	if (!is_wildcard(data))
		return (p_cmd);
	i = 0;
	matching = NULL;
	file_names = get_file_names(data);
	while (file_names && file_names[i])
	{
		while (file_names[i] && (*str)[0] != '.' && file_names[i][0] == '.')
			free(file_names[i++]);
		while (file_names[i] && (*str)[ft_strlen(*str) - 1] == '/' && \
		!is_dir(file_names[i]))
			free(file_names[i++]);
		if (file_names[i] && (*str)[ft_strlen(*str) - 1] == '/')
			file_names[i] = ft_stradd_char(data, file_names[i], '/');
		data->wc->file_name = file_names[i];
		if (file_names[i] && check_filename2(data, *str, 1))
			ft_cmdadd_back(&matching, ft_cmdnew(ft_strdup(file_names[i])));
		if (file_names[i])
			free(file_names[i++]);
	}
	return (free(file_names), finish_wc(data, matching, p_cmd));
}

char	small_expand(t_data *data, char **new_word, char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '$' && str[*i + 1] == '?')
			*new_word = ft_add_excode(data, *new_word, i);
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
				data->wc->wc_bin = ft_stradd_char(data, data->wc->wc_bin, '1');
			*new_word = ft_stradd_char(data, *new_word, str[(*i)++]);
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
			new_word = ft_add_excode(data, new_word, &i);
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
				data->wc->wc_bin = ft_stradd_char(data, data->wc->wc_bin, '0');
			new_word = ft_stradd_char(data, new_word, str[i++]);
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
				p_cmd = expand_wc(data, &p_cmd->content, p_cmd);
			}
		}
		p_cmd = p_cmd->next;
	}
	return (0);
}

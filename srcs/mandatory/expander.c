/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:23:06 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/09 04:56:51 by yridgway         ###   ########.fr       */
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
	search_for = ft_substr(data, str, 0, size);
	while (p_env && better_strncmp(p_env->name, search_for, size))
		p_env = p_env->next;
	if (p_env)
		new_word = ft_strjoin(data, new_word, p_env->content);
	ft_free(search_for);
	return (new_word);
}

char	small_expand(t_data *data, char **new_word, char *str, int *i)
{
	char	end;

	end = 0;
	while (str[*i])
	{
		if (data->expand && str[*i] == '$' && str[*i + 1] == '?')
			*new_word = ft_add_excode(data, *new_word, i);
		else if (data->expand && str[*i] == '$' && \
		(str[*i + 1] == 34 || str[*i + 1] == 39))
			(*i)++;
		else if (data->expand && str[*i] == '$' && (is_alphanum(str[*i + 1]) || \
		str[*i + 1] == '_'))
		{
			(*i)++;
			*new_word = replace_var(data, *new_word, str + *i);
			while (is_alphanum(str[*i]) || str[*i] == '_')
				(*i)++;
		}
		else if ((!data->expand && str[*i] == 34) || str[*i] == 39)
			return (str[(*i)++]);
		else
			*new_word = ft_stradd_char(data, *new_word, str[(*i)++]);
	}
	return (end);
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
		if (data->expand && str[i] == '$' && str[i + 1] == '?' && end == 34)
			new_word = ft_add_excode(data, new_word, &i);
		else if (data->expand && str[i] == '$' && (is_alphanum(str[i + 1]) || \
		str[i + 1] == '_') && end == 34)
		{
			i++;
			new_word = replace_var(data, new_word, str + i);
			while (is_alphanum(str[i]) || str[i] == '_')
				i++;
		}
		else
			new_word = ft_stradd_char(data, new_word, str[i++]);
	}
	if (!str[i])
		return (new_word);
	return (big_expand(data, new_word, str + i + 1));
}

int	ft_expander(t_data *data, int expand)
{
	char		*new_word;
	t_cmdline	*p_cmd;

	p_cmd = data->cmd;
	data->expand = expand;
	while (p_cmd)
	{
		if (p_cmd->type == WORD)
		{
			new_word = NULL;
			if (!better_strncmp(p_cmd->content, "\"\"", 2) || \
			!better_strncmp(p_cmd->content, "\'\'", 2))
			{
				ft_free(p_cmd->content);
				p_cmd->content = ft_strdup(data, "");
			}
			else
				fill_new_word(data, &new_word, &p_cmd);
		}
		p_cmd = p_cmd->next;
	}
	return (0);
}

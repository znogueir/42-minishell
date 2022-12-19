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
	t_env	*p_env;

	size = 0;
	p_env = data->loc_env;
	while (is_alphanum(str[size]) || str[size] == '_')
		size++;
	while (p_env && better_strncmp(p_env->name, str, size))
	{
		p_env = p_env->next;
	}
	if (p_env)
	{
		new_word = ft_strjoin(new_word, p_env->content);
	}
	return (new_word);
}

char	small_expand(t_data *data, char **new_word, char *str, int *i)
{
	char	end;

	end = 0;
	while (str[*i])
	{
		if (str[*i] == '$' && (is_alphanum(str[*i + 1]) || str[*i + 1] == '_'))
		{
			(*i)++;
			*new_word = replace_var(data, *new_word, str + *i);
			while (is_alphanum(str[*i]) || str[*i] == '_')
				(*i)++;
		}
		else if (str[*i] == '$' && str[*i + 1] == '?')
			*new_word = ft_add_excode(*new_word, i);
		else if (str[*i] == '$' && (str[*i + 1] == 34 || str[*i + 1] == 39))
			(*i)++;
		else if (str[*i] == 34 || str[*i] == 39)
			return (str[(*i)++]);
		else
			*new_word = ft_stradd_char(*new_word, str[(*i)++]);
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
	// ft_printf("%c", end);
	while (str[i] && str[i] != end)
	{
		if (str[i] == '$' && end == 34)
		{
			i++;
			new_word = replace_var(data, new_word, str + i);
			while (is_alphanum(str[i]) || str[i] == '_')
				i++;
		}
		else
			new_word = ft_stradd_char(new_word, str[i++]);
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
			}
		}
		p_cmd = p_cmd->next;
	}
	return (0);
}

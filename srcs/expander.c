/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:23:06 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/23 19:52:18 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_var(t_data *data, char *new_word, char *str)
{
	int		size;
	t_env	*p_env;

	size = 0;
	p_env = data->loc_env;
	while (is_alphanum(str[size]))
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

char	*ft_stradd_char(char *str, char c)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

char	small_expand(t_data *data, char **new_word, char *str, int *i)
{
	char	end;

	end = 0;
	while (str[*i])
	{
		if (str[*i] == '$' && is_alphanum(str[*i + 1]))
		{
			(*i)++;
			*new_word = replace_var(data, *new_word, str + *i);
			while (is_alphanum(str[*i]))
				(*i)++;
		}
		else if (str[*i] == 34 || str[*i] == 39)
		{
			end = str[*i];
			(*i)++;
			break ;
		}
		else
		{
			*new_word = ft_stradd_char(*new_word, str[*i]);
			(*i)++;
		}
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
		if (str[i] == '$' && end == 34)
		{
			i++;
			new_word = replace_var(data, new_word, str + i);
			while (is_alphanum(str[i]))
				i++;
		}
		else
		{
			new_word = ft_stradd_char(new_word, str[i]);
			i++;
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
			new_word = big_expand(data, new_word, p_cmd->content);
			free(p_cmd->content);
			p_cmd->content = new_word;
		}
		p_cmd = p_cmd->next;
	}
	return (0);
}

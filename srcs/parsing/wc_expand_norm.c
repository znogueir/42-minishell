/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_expand_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:03:34 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/02 20:03:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_mini_expand(t_data *data, char **str, char **new_word, int i)
{
	i++;
	*new_word = replace_var(data, *new_word, *str + i);
	while (is_alphanum((*str)[i]) || (*str)[i] == '_')
		i++;
	return (i);
}

int	wc_mini_expand(t_data *data, char **new_word, char **str, int i)
{
	if ((*str)[i] == '*')
		data->wc.wc_bin = ft_stradd_char(data, data->wc.wc_bin, '0');
	*new_word = ft_stradd_char(data, *new_word, (*str)[i++]);
	return (i);
}

t_env	*get_env_var(t_env *loc_env, char *name)
{
	while (loc_env && ft_strcmp(name, loc_env->name))
	{
		loc_env = loc_env->next;
	}
	return (loc_env);
}

void	replace_tilde(t_data *data, t_cmdline *p_cmd)
{
	t_env	*p_env;
	char	*tmp;

	p_env = get_env_var(data->loc_env, "HOME");
	if (!p_env || p_env->content[0] == '\0')
	{
		tmp = ft_strdup(data, p_cmd->content + 1);
		ft_free(p_cmd->content);
		p_cmd->content = tmp;
	}
	else
	{
		tmp = ft_strdup(data, p_cmd->content + 1);
		ft_free(p_cmd->content);
		p_cmd->content = (ft_strjoin(data, ft_strdup(data, \
		p_env->content), tmp));
		ft_free(tmp);
	}
}

void	fill_new_word(t_data *data, char **new_word, t_cmdline **p_cmd)
{
	if ((*p_cmd)->content[0] == '~' && (!(*p_cmd)->content[1] || \
	(*p_cmd)->content[1] == '/'))
		replace_tilde(data, *p_cmd);
	*new_word = big_expand(data, *new_word, (*p_cmd)->content);
	ft_free((*p_cmd)->content);
	(*p_cmd)->content = *new_word;
	(*p_cmd) = expand_wc(data, &(*p_cmd)->content, (*p_cmd));
}

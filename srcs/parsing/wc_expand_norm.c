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
		data->wc->wc_bin = ft_stradd_char(data, data->wc->wc_bin, '0');
	*new_word = ft_stradd_char(data, *new_word, (*str)[i++]);
	return (i);
}

void	fill_new_word(t_data *data, char **new_word, t_cmdline *p_cmd)
{
	*new_word = big_expand(data, *new_word, p_cmd->content);
	ft_free(p_cmd->content);
	p_cmd->content = *new_word;
	p_cmd = expand_wc(data, &p_cmd->content, p_cmd);
}

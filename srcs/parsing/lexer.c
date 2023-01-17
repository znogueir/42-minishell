/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:27:54 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

char	*malloc_token(t_data *data, char *str, int size)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_mallocator(data, sizeof(char) * (size + 1));
	if (!token)
		return (NULL);
	while (i < size)
	{
		token[i] = str[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

int	check_dbredir(char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] == '<') || \
	(str[i] == '>' && str[i + 1] == '>') || \
	(str[i] == '<' && str[i + 1] == '>'))
		return (1);
	return (0);
}

void	check_operator(t_data *data, int *i, int *ck_pt)
{
	if (check_dbredir(data->line, *i))
	{
		*i += 2;
		ft_cmdadd_back(&(data->cmd), \
		ft_cmdnew(malloc_token(data, data->line + *ck_pt, *i - *ck_pt)));
	}
	// else if (data->line[*i] == '#')
	// {
	// 	if (ft_strchr(" \t", data->line[*i - 1]))
	// 	{
	// 		while (data->line[*i] != '\n')
	// 			(*i)++;
	// 	}
	// 	else
	// 		return ;
	// }
	else
	{
		(*i)++;
		ft_cmdadd_back(&(data->cmd), \
		ft_cmdnew(malloc_token(data, data->line + *ck_pt, *i - *ck_pt)));
	}
}

void	lex_word(t_data *data, int *i, int *ck_pt)
{
	while (data->line[*i] && (!ft_strchr(SPE_CHARS, data->line[*i]) \
	|| data->quote))
	{
		if (data->line[*i] == 34 && !(data->quote))
			data->quote = 2;
		else if (data->line[*i] == 39 && !(data->quote))
			data->quote = 1;
		else if ((data->line[*i] == 34 && data->quote == 2) || \
		(data->line[*i] == 39 && data->quote == 1))
			data->quote = 0;
		(*i)++;
	}
	ft_cmdadd_back(&(data->cmd), \
	ft_cmdnew(malloc_token(data, data->line + *ck_pt, *i - *ck_pt)));
}

int	ft_lexer(t_data *data)
{
	int			i;
	int			ck_pt;

	i = 0;
	ck_pt = 0;
	while (data->line && data->line[i])
	{
		while (data->line[i] && ft_strchr(" \t\n", data->line[i]) && \
		!(data->quote))
			i++;
		ck_pt = i;
		if (data->line[i] && ft_strchr(OPS, data->line[i]) && !(data->quote))
		{
			check_operator(data, &i, &ck_pt);
		}
		else if (data->line[i] && (!ft_strchr(SPE_CHARS, data->line[i]) || \
		data->quote))
		{
			lex_word(data, &i, &ck_pt);
		}
	}
	return (0);
}

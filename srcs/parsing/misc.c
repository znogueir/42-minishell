/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:53:28 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/15 18:42:58 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_uppercmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] >= 'A' && s1[i] <= 'Z' && s1[i] == s2[i] - 32)
			return (-1);
		i++;
	}
	return (1);
}

int	ft_alphacmp(char *s1, char *s2)
{
	size_t			i;
	char			s1_f;
	char			s2_f;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		s1_f = s1[i];
		s2_f = s2[i];
		if (s1[i] >= 'A' && s1[i] <= 'Z')
			s1_f += 32;
		if (s2[i] >= 'A' && s2[i] <= 'Z')
			s2_f += 32;
		if (s1_f != s2_f)
			return (s2_f - s1_f);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (ft_uppercmp(s1, s2));
	return (s2[i] - s1[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	better_strncmp(char *s1, char *s2, int size)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != (size_t)size || ft_strlen(s2) != (size_t)size || \
	!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && i < size)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_alphanum(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || \
	(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	print_list(t_cmdline *cmd)
{
	if (cmd)
		ft_printf("\n");
	while (cmd)
	{
		ft_printf("\t{%s%s%s}", ORANGE, cmd->content, RES_COL);
		ft_printf(" - type : %s\n" RES_COL, convert_type(cmd->type));
		cmd = cmd->next;
	}
	if (cmd)
		ft_printf("\n");
}

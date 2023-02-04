/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:04:15 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/01 20:24:50 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_wc_exp(char **file_names, char *str, int *i)
{
	while (file_names[*i] && str[0] != '.' && file_names[*i][0] == '.')
		ft_free(file_names[(*i)++]);
	while (file_names[*i] && str[ft_strlen(str) - 1] == '/' && \
	!is_dir(file_names[*i]))
		ft_free(file_names[(*i)++]);
}

t_cmdline	*finish_wc(t_data *data, t_cmdline *matching, t_cmdline *p_cmd)
{
	t_cmdline	*tmp;
	t_cmdline	*ret;

	ret = p_cmd;
	if (matching)
	{
		tmp = p_cmd->next;
		ft_free(p_cmd->content);
		p_cmd->content = ft_strdup(data, matching->content);
		if (matching->next)
		{
			p_cmd->next = matching->next;
			ret = get_last_cmd(matching);
			ret->next = tmp;
		}
		ft_free(matching->content);
		ft_free(matching);
	}
	ft_free(data->wc->wc_bin);
	data->wc->wc_bin = NULL;
	return (ret);
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

int	is_wildcard(t_data *data)
{
	int	i;

	i = 0;
	while (data->wc->wc_bin && data->wc->wc_bin[i])
	{
		if (data->wc->wc_bin[i] == '1')
			return (1);
		i++;
	}
	ft_free(data->wc->wc_bin);
	data->wc->wc_bin = NULL;
	return (0);
}

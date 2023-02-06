#include "minishell.h"

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
}
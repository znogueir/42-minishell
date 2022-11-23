/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:10:24 by znogueir          #+#    #+#             */
/*   Updated: 2022/11/23 19:52:50 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_prompt(void)
{
	ft_printf(PROMPT);
}

void	write_error(char *error_msg)
{
	write(2, ERR_PRE, ft_strlen(ERR_PRE));
	write(2, error_msg, ft_strlen(error_msg));
}

int	ft_check_exit(char *line)
{
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if (!ft_strncmp(line, "exit", 4) && (*(line + 4) == ' ' || \
	(*(line + 4) >= 9 && *(line + 4) <= 13)))
	{
		write(1, "bye! 👋\n", 11);
		return (0);
	}
	return (1);
}

t_data	*ft_init(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->quote = 0;
	data->line = NULL;
	data->loc_env = NULL;
	data->cmd = NULL;
	set_env(env, data);
	ft_envadd_back(&(data->loc_env), ft_envnew(ft_strdup("truc"), ft_strdup("machin")));
	ft_envadd_back(&(data->loc_env), ft_envnew(ft_strdup("abc"), ft_strdup("abracadabra")));
	ft_envadd_back(&(data->loc_env), ft_envnew(ft_strdup("blabla"), ft_strdup("banana")));
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_data		*data;

	(void)ac;
	(void)av;
	data = ft_init(env);
	//check_builtins(data);
	write_prompt();
	data->line = get_next_line(0);
	while (ft_check_exit(data->line))
	{
		if (!check_errors(data->line))
		{
			ft_lexer(data);
			print_list(data->cmd);
			if (!ft_parser(data))
			{
				ft_expander(data);
				ft_printf("---------------expand---------------\n");
				print_list(data->cmd);
				//ft_env(data->loc_env);
			}
			reset_cmd(data);
		}
		free(data->line);
		write_prompt();
		data->line = get_next_line(0);
	}
	free_all(data);
	return (0);
}

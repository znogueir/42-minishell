/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:10:24 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/08 21:56:27 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_prompt(void)
{
	ft_printf(PROMPT);
}

void	write_error(char *error_msg)
{
	write(2, ERR_PRE, ft_strlen(ERR_PRE));
	write(2, error_msg, ft_strlen(error_msg));
}

// int	ft_check_exit(char *line)
// {
// 	while ((*line == ' ' || (*line >= 9 && *line <= 13)))
// 		line++;
// 	if (!ft_strncmp(line, "exit", 4) && (*(line + 4) == ' ' || 
// 	(*(line + 4) >= 9 && *(line + 4) <= 13)))
// 	{
// 		write(1, "bye! 👋\n", 11);
// 		return (0);
// 	}
// 	return (1);
// }

int	ft_check_exit(char *line)
{
	if (!ft_strncmp(line, "exit", 4))
	{
		if (line[4] > 32)
			return (1);
		else
		{
			write(1, "bye! 👋\n", 11);
			return (0);
		}
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
	//data->cmdtable = NULL;
	data->filelist = NULL;
	set_env(env, data);
	// ft_export(data, ft_strdup("tru"), ft_strdup("machin"));
	// ft_export(data, ft_strdup("trucs"), ft_strdup("abracadabra"));
	// ft_export(data, ft_strdup("truc"), ft_strdup("banana"));
	return (data);
}

void	check_env(t_data *data)
{
	ft_export(data, ft_strdup("TEST1"), ft_strdup("machin"), 0);
	ft_export(data, ft_strdup("TEST2"), ft_strdup("abra"), 1);
	ft_env(data->loc_env);
	ft_printf("--------TEST CONTRAIRE--------\n");
	ft_export(data, ft_strdup("TEST1"), ft_strdup("+truc"), 1);
	ft_export(data, ft_strdup("TEST2"), ft_strdup("{blabla}"), 0);
	ft_env(data->loc_env);
}

void	print_tab(char **tab);

int	main(int ac, char **av, char **env)
{
	t_data		*data;

	(void)ac;
	(void)av;
	data = ft_init(env);
	// check_env(data);
	//signal_handler();
	// check_builtins(data);
	data->line = readline(PROMPT);
	add_history(data->line);
	while (ft_check_exit(data->line))
	{
		if (!check_errors(data->line))
		{
			ft_lexer(data);
			//print_list(data->cmd);
			if (!ft_parser(data))
			{
				ft_expander(data);
				//print_tab(data->paths);
				//print_list(data->cmd);
				ft_executor(data, env);
				// ft_env(data->loc_env);
			}
			reset_cmd(data);
		}
		free(data->line);
		data->line = readline(PROMPT);
		add_history(data->line);
	}
	//free(str);
	free_all(data);
	return (0);
}

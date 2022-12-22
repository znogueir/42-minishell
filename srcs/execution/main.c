/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:10:24 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/18 23:13:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

void	reset_cmd(t_data *data)
{
	free_cmd(data->cmd);
	data->cmd = NULL;
}

void	write_error(char *error_msg)
{
	ft_putstr_fd(ERR_PRE, 2);
	ft_putstr_fd(error_msg, 2);
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
	data->cmdtable = NULL;
	data->filelist = NULL;
	data->char_env = NULL;
	set_env(env, data);
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_data		*data;
	// char		*temp;
	(void)ac;
	(void)av;
	data = ft_init(env);
	while (1)
	{
		// temp = readline(NULL);
		// if (temp && temp[0] == '\0')
		// 	exit(0);
		// data->line = get_next_line(0);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		rl_outstream = stderr;
		data->line = readline(PROMPT);
		if (!data->line)
			break ;
		add_history(data->line);
		if (check_errors(data->line))
		{
			// reset_cmd(data);
			// free(data->line);
			// continue ;
			break ;
		}
		ft_lexer(data);
		if (!ft_parser(data))
		{
			// print_list(data->cmd);
			ft_expander(data);
			// print_list(data->cmd);
			ft_executor(data, env);
		}
		reset_cmd(data);
		free(data->line);
	}
	free_all(data);
	return (0);
}

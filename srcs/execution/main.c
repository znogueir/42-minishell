/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:10:24 by znogueir          #+#    #+#             */
/*   Updated: 2023/01/04 18:27:42 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

void	reset_cmd(t_data *data)
{
	free_cmd(data->cmd);
	data->cmd = NULL;
}

t_data	*ft_init(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->quote = 0;
	data->line = NULL;
	data->wildcards = NULL;
	data->loc_env = NULL;
	data->cmd = NULL;
	data->cmdtable = NULL;
	data->filelist = NULL;
	data->char_env = NULL;
	data->open_pipe = 0;
	data->hdoc_open = 0;
	data->hdoc_write = 0;
	data->wc = malloc(sizeof(t_wildcards));
	memset(data->wc, 0, sizeof(t_wildcards));
	// data->wc->wc_bin = NULL;
	// data->wc->file_name = NULL;
	set_env(env, data);
	return (data);
}

int	ft_launch_minishell(char *line, char **env)
{
	t_data		*data;
	int			exit_status;

	data = ft_init(env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	data->line = ft_strdup(line);
	// if (!data->line)
	// 	break ;
	add_history(data->line);
	//printf("data->line: %s\n", data->line);
	if (!check_errors(data->line))
	{
		// reset_cmd(data);
		// free(data->line);
		// continue ;
		// ft_exit_fork(data, NULL, 0);
		ft_lexer(data);
		exit_status = ft_parser(data);
		if (!exit_status)
		{
			// print_list(data->cmd);
			ft_expander(data);
			// print_list(data->cmd);
			ft_executor(data, env);
		}
		else
			g_exit = exit_status;
	}
	reset_cmd(data);
	//free(data->line);
	free_all(data);
	return (g_exit);
}

int	launch_normal(int ac, char **av, char **env)
{
	t_data		*data;
	int			exit_status;
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
			reset_cmd(data);
			free(data->line);
			continue ;
			// break ;
		}
		ft_lexer(data);
		exit_status = ft_parser(data);
		if (!exit_status)
		{
			// print_list(data->cmd);
			ft_expander(data);
			// print_list(data->cmd);
			ft_executor(data, env);
		}
		else
			g_exit = exit_status;
		reset_cmd(data);
		free(data->line);
	}
	free_all(data);
	return (g_exit);
}

int	main(int argc, char **argv, char **env)
{
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		ft_launch_minishell(argv[2], env);
	else
		launch_normal(argc, argv, env);
	exit(g_exit);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_data		*data;
// 	// char		*temp;

// 	(void)ac;
// 	(void)av;
// 	// printf("av: %s\n", av[1]);
// 	data = ft_init(env);
// 	while (1)
// 	{
// 		// temp = readline(NULL);
// 		// if (temp && temp[0] == '\0')
// 		// 	exit(0);
// 		// data->line = get_next_line(0);
// 		signal(SIGINT, handle_sigint);
// 		signal(SIGQUIT, SIG_IGN);
// 		rl_outstream = stderr;
// 		data->line = readline(PROMPT);
// 		if (!data->line)
// 			break ;
// 		add_history(data->line);
// 		//printf("data->line: %s\n", data->line);
// 		if (check_errors(data->line))
// 		{
// 			// reset_cmd(data);
// 			// free(data->line);
// 			// continue ;
// 			break ;
// 		}
// 			// ft_exit_fork(data, NULL, 0);
// 		ft_lexer(data);
// 		if (!ft_parser(data))
// 		{
// 			// print_list(data->cmd);
// 			ft_expander(data);
// 			// print_list(data->cmd);
// 			ft_executor(data, env);
// 		}
// 		reset_cmd(data);
// 		free(data->line);
// 	}
// 	//ft_putstr_fd("exit", 1);
// 	free_all(data);
// 	return (0);
// }

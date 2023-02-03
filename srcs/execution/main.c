/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:10:24 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/02 19:23:55 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;
int	break_malloc_at = 5760;
int	cur_breakpoint = 100000;

void	reset_cmd(t_data *data)
{
	free_cmd(data->cmd);
	data->cmd = NULL;
}

t_data	ft_init(char **env)
{
	t_data	data;

	data.quote = 0;
	data.line = NULL;
	data.loc_env = NULL;
	data.cmd = NULL;
	data.cmdtable = NULL;
	data.filelist = NULL;
	data.char_env = NULL;
	data.open_pipe = 0;
	data.hdoc_open = 0;
	data.hdoc_write = 0;
	data.insave = dup(0);
	data.outsave = dup(1);
	data.wc = ft_malloc(NULL, &data, sizeof(t_wildcards));
	data.wc->wc_bin = NULL;
	set_env(env, &data);
	return (data);
}

int	launch_normal(int ac, char **av, char **env)
{
	t_data		data;
	int			exit_status;

	(void)ac;
	(void)av;
	data = ft_init(env);
	while (g_exit != 256)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		//rl_outstream = stderr;
		if (g_exit == 256)
			break ;
		data.line = readline(PROMPT);
		if (!data.line)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		add_history(data.line);
		if (check_errors(data.line))
		{
			ft_free(data.line);
			// data.line = NULL;
			reset_cmd(&data);
			// free_all(&data);
			continue ;
		}
		ft_lexer(&data);
		exit_status = ft_parser(&data);
		if (!exit_status)
		{
			ft_expander(&data);
			ft_executor(&data, env);
		}
		else
			g_exit = exit_status;
		ft_free(data.line);
		reset_cmd(&data);
	}
	// free_all(&data);
	ft_quit(&data);
	return (g_exit);
}

int	ft_launch_minishell(char *line, char **env)
{
	t_data		data;
	int			exit_status;

	data = ft_init(env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	data.line = ft_strdup(&data, line);
	add_history(data.line);
	if (!check_errors(data.line))
	{
		ft_lexer(&data);
		exit_status = ft_parser(&data);
		if (!exit_status)
		{
			ft_expander(&data);
			ft_executor(&data, env);
		}
		else
			g_exit = exit_status;
	}
	reset_cmd(&data);
	free_all(&data);
	return (g_exit);
}

int	main(int argc, char **argv, char **env)
{
	char	**cmds;
	int		i;

	i = 0;
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		cmds = ft_split(NULL, argv[2], ";");
		while (cmds[i])
			ft_launch_minishell(cmds[i++], env);
	}
	else
		launch_normal(argc, argv, env);
	exit(g_exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:23:51 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/07 19:50:09 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include "minishell.h"

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	*validcmd1;
	char	*validcmd2;
	int		pipefd[2];
	int		infd;
	int		outfd;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

//finish
void	ft_error(char *extra);
void	ft_exit_msg(char *msg);
void	close_free(t_pipex *pipex);
void	ft_free_arr(char **cmd);
void	ft_end(t_pipex *pipex);
void	free_things(char **one, char **two, char *three);

//children
void	ft_pipe(t_cmdtable *table, char **cmd, char **env);
void	ft_execute(char **cmd, char **env);

//exits
int		ft_permission_denied(char *prog);
int		ft_command_not_found(char *prog);
int		ft_no_such_file(char *prog);

//paths
char	**ft_get_paths(char **env);
int		check_path(char *prog, char *cmdpath);
char	*ft_join_path(char *path, char *prog);
char	*get_valid_path(char **env, char **prog);

//utils
char	*ft_strjoin_2(char *s1, char *s2);

#endif

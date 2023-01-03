/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:38:49 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/22 00:34:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_cmdline
{
	char				*content;
	int					type;
	struct s_cmdline	*next;
}						t_cmdline;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct s_filelist
{
	int					fd;
	int					type;
	int					order;
	char				*filename;
	struct s_filelist	*next;
}						t_filelist;

typedef struct s_cmdtable
{
	char				**cmd;
	int					status;
	t_filelist			*infile;
	t_filelist			*outfile;
	struct s_cmdtable	*next;
}						t_cmdtable;

typedef struct s_data
{
	int			quote;
	char		*line;
	char		*wildcards;
	char		**paths;
	char		**char_env;
	t_env		*loc_env;
	t_cmdline	*cmd;
	t_cmdtable	*cmdtable;
	t_filelist	*filelist;
	int			pipe[2];
	int			insave;
	int			outsave;
	int			pid;
	int			open_pipe;
}				t_data;

#endif

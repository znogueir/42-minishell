/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:38:49 by yridgway          #+#    #+#             */
/*   Updated: 2022/12/09 18:55:59 by yridgway         ###   ########.fr       */
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
	char				*filename;
	int					type;
	int					order;
	struct s_filelist	*next;
}						t_filelist;

typedef struct s_cmdtable
{
	char				**cmd;
	t_filelist			*infile;
	t_filelist			*outfile;
	int					status;
	struct s_cmdtable	*next;
}						t_cmdtable;

typedef struct s_data
{
	int			quote;
	char		*line;
	char		**paths;
	char		**char_env;
	t_env		*loc_env;
	t_cmdline	*cmd;
	t_cmdtable	*cmdtable;
	t_filelist	*filelist;
	int			pipe[2];
	int			insave;
}				t_data;

#endif

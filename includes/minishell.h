/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:17:38 by znogueir          #+#    #+#             */
/*   Updated: 2022/12/04 21:23:25 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/gnl/get_next_line.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "pipex.h"

/*--------------------------------------------------*/
/*				   	   Operators				   	*/
/*--------------------------------------------------*/

// operators :
// |  &  <  >  (  )  $  `  "  '  <newline>
// *   ?   [   #   ˜   =   %
// white space : <space> <tab>

// deprec_operators:
// \  ;

# define SPE_CHARS "|<> \t\n"
# define OPS "#|<>\n"
# define WH_SPC " \t"

/*--------------------------------------------------*/
/*				   	    Tokens				   		*/
/*--------------------------------------------------*/
# define WORD 0
# define PIPE 1/* | */
# define LESS 2/* < */
# define GREAT 3/* > */
# define H_DOC 4/* << */
# define APPEND 5/* >> */
# define LESSGREAT 6/* <> */
# define NEWLINES 7/* \n */

/*--------------------------------------------------*/
/*				   	    Colors				   		*/
/*--------------------------------------------------*/
# define PINK "\e[38;5;201;1m"
# define PURPLE "\e[38;5;93;1m"
# define BLUE "\e[38;5;27;1m"
# define CYAN "\e[38;5;51;1m"
# define GREEN "\e[38;5;46;1m"
# define YELLOW "\e[38;5;226;1m"
# define ORANGE "\e[38;5;208;1m"
# define RED "\e[38;5;1;1m"
# define RES_COL "\e[0m"

/*--------------------------------------------------*/
/*					   Prompts				   		*/
/*--------------------------------------------------*/
# define ERR_PRE "\e[38;5;1;1mx\e[0m minishell: "
# define PROMPT	"\e[38;5;46;1mminishell$>\e[0m "

/*--------------------------------------------------*/
/*					   Structs				   		*/
/*--------------------------------------------------*/
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
	char				*limiter;
	int					type;
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
	t_env		*loc_env;
	t_cmdline	*cmd;
	t_cmdtable	*cmdtable;
	t_filelist	*filelist;
}				t_data;

/*--------------------------------------------------*/
/*				   	  Functions		   				*/
/*--------------------------------------------------*/
//	free
void		free_split(char **tab);
void		reset_cmd(t_data *data);
void		free_cmd(t_cmdline *cmd);
void		free_env(t_env *loc_env);
void		free_table(t_cmdtable *table);
void		free_all(t_data *data);
void		free_files(t_filelist *filelist);

// pre_lex
int			check_errors(char *line);

//	lexer
int			ft_lexer(t_data *data);

//	parser
void		write_error(char *error_msg);
int			ft_parser(t_data *data);

//	expander
int			ft_expander(t_data *data);

//	list functs
void		print_list(t_cmdline *cmd);
t_cmdline	*ft_cmdnew(void *content);
t_env		*ft_envnew(char *name, char *content);
t_cmdtable	*ft_tablenew(char **cmd, char *operator, int type);
t_filelist	*ft_filenew(int fd, char *filename, char *limiter, int type);
void		ft_cmdadd_back(t_cmdline **lst, t_cmdline *new);
void		ft_envadd_back(t_env **lst, t_env *new);
void		ft_tableadd_back(t_cmdtable **lst, t_cmdtable *new);
void		ft_fileadd_back(t_filelist **lst, t_filelist *new);

//	builtins
int			ft_cd(char *path);
int			ft_echo(char *str, int newline);
int			ft_env(t_env *loc_env);
int			ft_exit(void);
int			ft_export(t_data *data, char *name, char *content);
int			ft_pwd(void);
int			ft_unset(t_data *data, char *name);

//	builtin utils
void		set_env(char **env, t_data *data);

// utils
int			is_alphanum(char c);
int			is_redir(int type);
int			better_strncmp(char *s1, char *s2, int size);

// miscellaneous
void		check_builtins(t_data *data);
void		print_colors(void);

//	token types
int			find_token_type(char *token);
char		*convert_type(int type);

// executor
int			ft_executor(t_data *data, char **env);
void		display_cmdtable(t_cmdtable *table);
void		make_cmdtable(t_data *data);
void		close_files(t_cmdtable *table);
#endif

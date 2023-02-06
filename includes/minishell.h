/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:17:38 by znogueir          #+#    #+#             */
/*   Updated: 2023/02/06 20:11:12 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "structures.h"
# include "pipex.h"

extern int	g_exit;
extern int	break_malloc_at;
extern int	cur_breakpoint;

/*----------------------------------------------------------------------------*/
/*									Operations								  */
/*----------------------------------------------------------------------------*/

# define SPE_CHARS "|<> \t\n"
# define OPS "#|<>\n"
# define WH_SPC " \t"

/*----------------------------------------------------------------------------*/
/*									  Memory								  */
/*----------------------------------------------------------------------------*/
# define EXIT_FREE -777
# define FREE_ALL -666
# define ADD_TO_MEM -555
// # define FREE_ONE -555

/*----------------------------------------------------------------------------*/
/*									  Tokens								  */
/*----------------------------------------------------------------------------*/
# define WORD 0
# define PIPE 1/* | */
# define LESS 2/* < */
# define GREAT 3/* > */
# define H_DOC 4/* << */
# define APPEND 5/* >> */
# define LESSGREAT 6/* <> */
# define NEWLINES 7/* \n */

/*----------------------------------------------------------------------------*/
/*									 Colors									  */
/*----------------------------------------------------------------------------*/
// # define RED "\e[38;5;1;1m"
// # define BLUE "\e[38;5;27;1m"
// # define CYAN "\e[38;5;51;1m"
// # define GREEN "\e[38;5;46;1m"
// # define PINK "\e[38;5;201;1m"
// # define PURPLE "\e[38;5;93;1m"
// # define ORANGE "\e[38;5;208;1m"
// # define YELLOW "\e[38;5;226;1m"
// # define RES_COL "\e[0m"

/*----------------------------------------------------------------------------*/
/*									 Prompts								  */
/*----------------------------------------------------------------------------*/

# define ERR_PRE "\e[38;5;1;1mx\e[0m minishell: syntax error"
# define PROMPT	"minishell$> "

/*----------------------------------------------------------------------------*/
/*									Execution								  */
/*----------------------------------------------------------------------------*/
# define IN "/dev/stdin"
# define OUT "/dev/stdout"

/*----------------------------------------------------------------------------*/
/*									Functions								  */
/*----------------------------------------------------------------------------*/

//	free
void		ft_free(void *thing);
// void		free_all(t_data *data);
void		ft_add_to_mem(t_data *data, void *thing);
void		clean_memory(t_data *data);
void		ft_close(int *fd);
void		ft_quit(t_data *data);
// void		free_all(t_data *data);
void		free_split(char **tab);
void		reset_cmd(t_data *data);
void		free_cmd(t_cmdline *cmd);
void		free_env(t_env *loc_env);
void		free_files(t_filelist *filelist);
void		free_table(t_data *data, t_cmdtable *table);
// void		ft_exit_fork(t_data *data, char **command, int ext);
void		*ft_mallocator(void *extra, t_data *data, int size);
void		ft_malloc_exit(void *extra, t_data *data);
// void		free_process(t_process *process);

//	pre_lex
int			check_errors(char *line);

//	lexer
int			ft_lexer(t_data *data);

//	parser
int			ft_parser(t_data *data);
void		write_error(char *error_msg, char *token);

//	expander
int			ft_expander(t_data *data);
char		*ft_stradd_char(t_data *data, char *str, char c);
char		*ft_add_excode(t_data *data, char *str, int *p_i);
char		*replace_var(t_data *data, char *new_word, char *str);

//	list functs
void		print_list(t_cmdline *cmd);
void		ft_envadd_back(t_env **lst, t_env *new);
void		ft_cmdadd_back(t_cmdline **lst, t_cmdline *new);
void		ft_fileadd_back(t_filelist **lst, t_filelist *new);
void		ft_tableadd_back(t_cmdtable **lst, t_cmdtable *new);
// void		ft_pidadd_back(t_process **lst, int pid);
t_env		*ft_envnew(t_data *data, char *name, char *content, int is_env);
t_cmdline	*ft_cmdnew(t_data *data, void *content);
t_cmdline	*ft_cmdpop(t_cmdline **cmdline, t_cmdline *topop);
t_cmdtable	*ft_tablenew(t_data *data);
t_cmdtable	*get_last(t_cmdtable *table);
t_filelist	*file_get_last(t_filelist *filelist);
t_filelist	*ft_filenew(t_data *data, int fd, char *filename, int type);
// t_process	*ft_pidnew(int pid);

//	builtins
int			ft_cd(t_data *data, char **cmd);
int			ft_echo(char **cmd, int newline);
int			ft_env(t_env *loc_env, char **cmd);
int			ft_exit(t_data *data, char **cmd);
int			ft_export(t_data *data, char *name, char *content, int append);
int			ft_pwd(void);
int			ft_unset(t_data *data, char **cmd);

//	builtin utils
int			is_builtin(char **command);
int			parse_export(char **cmd, t_data *data);
int			exec_builtin(char **command, t_data *data);
void		set_env(char **env, t_data *data);
void		update_env(char	**env, t_data *data);
void		print_export(char *name, char *content);
int			get_env_len(t_env **p_env, t_env **env_min);

// utils
int			is_redir(int type);
int			is_alphanum(char c);
int			better_strncmp(char *s1, char *s2, int size);
void		print_tab(char **tab);
void		print_echo(char	**cmd);

void		convert_env(t_data *data, t_env *loc_env);
char		**ft_arr_dup(t_data *data, char **arr);
void		display_cmdtable(t_cmdtable *table);

//	signals
// void		signal_handler(void);
void		sig_in_fork(int sig);
void		handle_sigint(int sig);
// void		handle_signals_v2(int sig);
void		handle_sig_heredocs(int sig);

//	miscellaneous
int			ft_strcmp(char *s1, char *s2);
int			ft_alphacmp(char *s1, char *s2);
void		print_colors(void);
void		check_builtins(t_data *data);

//	token types
int			find_token_type(char *token);
char		*convert_type(int type);

//	executor
int			make_cmdtable(t_data *data);
int			ft_executor(t_data *data, char **env);
// void		display_cmdtable(t_cmdtable *table);

//	wildcards
int			is_dir(char *name);
int			is_wildcard(t_data *data);
int			check_filename3(t_data *data, char *pattern);
int			dollar_mini_expand(t_data *data, char **str, \
char **new_word, int i);
int			wc_mini_expand(t_data *data, char **new_word, char **str, int i);
char		**get_file_names(t_data *data);
char		*big_expand(t_data *data, char *new_word, char *str);
void		mini_wc_exp(char **file_names, char *str, int *i);
void		fill_new_word(t_data *data, char **new_word, t_cmdline **p_cmd);
t_cmdline	*get_last_cmd(t_cmdline *files);
t_cmdline	*expand_wc(t_data *data, char **str, t_cmdline *p_cmd);
t_cmdline	*finish_wc(t_data *data, t_cmdline *matching, t_cmdline *p_prev);

//	open_close
int			ft_infile_open(t_data *data, t_cmdtable *table, t_cmdline *line);
int			ft_outfile_open(t_data *data, t_cmdtable *table, \
			t_cmdline *line, int settings);
int			ft_here_doc_open(t_data *data, t_cmdtable *table, t_cmdline *line, \
			int count);
int			ft_here_doc_write(t_data *data, char *limiter, int count);
int			ft_here_doc(t_data *data, t_cmdline *cmdline);
int			ft_fill_files(t_data *data, t_cmdtable *table, t_cmdline *cmdline);

// fd handling
void		ft_check_fds(t_cmdtable *table);
void		ft_close_pipes(t_data *data);

// E_X_T_R_A
void		*break_malloc(int size);
void		print_list(t_cmdline *cmd);

// tools
int			ft_atoi(const char *nptr);
char		*ft_itoa(t_data *data, int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(t_data *data, char const *s, char *sep);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(t_data *data, const char *s);
char		*ft_strjoin(t_data *data, char const *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		*ft_substr(t_data *data, char const *s, \
			unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		ft_putnbr_fd(int n, int fd);
int			ft_toupper(int c);
int			ft_isalpha(int c);

void		*ft_malloc(void *free, t_data *data, long long int size);
void		mem_clean(t_data *data, t_mem *mem);
void		ft_free_one(t_mem *mem, void *thing);

#endif

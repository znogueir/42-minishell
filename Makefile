CC		= cc
FLAGS	= -Wall -Wextra -Werror -g3
INCFLAGS= -lreadline
NAME	= minishell

# LIBFT_PATH	= libft/
# LIBFT			= $(LIBFT_PATH)libft.a

OBJ_PATH		= objs/
PARSE_OBJ_PATH	= objs/parsing/
BUILT_OBJ_PATH	= objs/builtins/
EXEC_OBJ_PATH	= objs/execution/
TOOL_OBJ_PATH	= objs/tools/

SRC_PATH		= srcs/
BUILT_PATH		= $(SRC_PATH)builtins/
EXEC_PATH		= $(SRC_PATH)execution/
PARSE_PATH		= $(SRC_PATH)parsing/
TOOLS_PATH		= $(SRC_PATH)tools/
INC_PATH		= includes/
INC_FILES		= $(INC_PATH)pipex.h $(INC_PATH)minishell.h $(INC_PATH)structures.h

PARSE	= wc_expander.c \
		wc_expand_norm.c \
		wc_filenames.c \
		wc_utils.c \
		wc_matching.c \
		free.c \
		free_2.c \
		lexer.c \
		lst_new.c \
		lst_addback.c \
		lst_utils.c \
		misc.c \
		parser.c \
		token_types.c \
		str_add.c

BUILTIN	= cd.c \
		echo.c \
		env.c \
		exit.c \
		export.c \
		pwd.c \
		unset.c \
		exec_builtins.c \
		builtin_utils.c

EXEC	= main.c \
		ft_executor.c \
		exec_parsing.c \
		children.c \
		exits.c \
		finish.c \
		paths.c \
		open.c \
		signals.c \
		fd_handling.c \
		utils.c \
		here_doc.c \
		extra.c

TOOL	= ft_atoi.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_substr.c \
		ft_strncmp.c \
		ft_putnbr_fd.c \
		ft_isalpha.c \
		ft_toupper.c \
		memory.c 

PARSES		= $(addprefix $(PARSE_PATH), $(PARSE))
BUILTINS	= $(addprefix $(BUILT_PATH), $(BUILTIN))
EXECS		= $(addprefix $(EXEC_PATH), $(EXEC))
TOOLS		= $(addprefix $(TOOLS_PATH), $(TOOL))
PARSE_OBJS	= $(addprefix $(PARSE_OBJ_PATH), $(PARSE:.c=.o))
BUILT_OBJS	= $(addprefix $(BUILT_OBJ_PATH), $(BUILTIN:.c=.o))
EXEC_OBJS	= $(addprefix $(EXEC_OBJ_PATH), $(EXEC:.c=.o))
TOOLS_OBJS	= $(addprefix $(TOOL_OBJ_PATH), $(TOOL:.c=.o))

OBJECTS		= $(PARSE_OBJS) $(BUILT_OBJS) $(EXEC_OBJS) $(TOOLS_OBJS)
OBJECT_PATHS= $(PARSE_OBJ_PATH) $(BUILT_OBJ_PATH) $(EXEC_OBJ_PATH) $(TOOL_OBJ_PATH)

all: $(NAME)

$(OBJ_PATH) $(OBJECT_PATHS) $(TOOL_OBJ_PATH)ft_printf:
	mkdir $(OBJ_PATH) $(OBJECT_PATHS) $(TOOL_OBJ_PATH)/ft_printf

$(PARSE_OBJ_PATH)%.o:$(PARSE_PATH)%.c $(INC_FILES)
	$(CC) $(FLAGS) -c $< $ -I$(INC_PATH) -o $@

$(BUILT_OBJ_PATH)%.o:$(BUILT_PATH)%.c $(INC_FILES)
	$(CC) $(FLAGS) -c $< $ -I$(INC_PATH) -o $@

$(EXEC_OBJ_PATH)%.o:$(EXEC_PATH)%.c $(INC_FILES)
	$(CC) $(FLAGS) -c $< $ -I$(INC_PATH) -o $@

$(TOOL_OBJ_PATH)%.o:$(TOOLS_PATH)%.c $(INC_FILES)
	$(CC) $(FLAGS) -c $< $ -I$(INC_PATH) -o $@

$(NAME): $(OBJECT_PATHS) $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(INCFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean:clean
	rm -f $(NAME)

run: $(NAME)
	clear
	valgrind  --exit-on-first-error=no --suppressions=readline.supp --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./minishell

re: fclean all

.PHONY: all clean fclean re run

CC		= gcc
FLAGS	= -g3 -Wall -Wextra -Werror
INCFLAGS= -lreadline
NAME	= minishell

LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)libft.a

OBJ_PATH		= objs/
PARSE_OBJ_PATH	= objs/parsing/
BUILT_OBJ_PATH	= objs/builtins/
EXEC_OBJ_PATH	= objs/execution/

SRC_PATH		= srcs/
BUILT_PATH		= $(SRC_PATH)builtins/
EXEC_PATH		= $(SRC_PATH)execution/
PARSE_PATH		= $(SRC_PATH)parsing/
INC_PATH		= includes/
INC_FILES		= $(INC_PATH)pipex.h $(INC_PATH)minishell.h

PARSE	= check_init.c \
		expander.c \
		free.c \
		lexer.c \
		lst_functs.c \
		main.c \
		misc.c \
		parser.c \
		token_types.c \

BUILTIN	= cd.c \
		echo.c \
		env.c \
		exit.c \
		export.c \
		pwd.c \
		unset.c \

EXEC	= ft_executor.c \
		exec_parsing.c \
		children.c \
		exits.c \
		finish.c \
		paths.c \
		open_close.c \

PARSES		= $(addprefix $(PARSE_PATH), $(PARSE))
BUILTINS	= $(addprefix $(BUILT_PATH), $(BUILTIN))
EXECS		= $(addprefix $(EXEC_PATH), $(EXEC))
PARSE_OBJ	= $(PARSE:.c=.o)
BUILT_OBJ	= $(BUILTIN:.c=.o)
EXEC_OBJ	= $(EXEC:.c=.o)
PARSE_OBJS	= $(addprefix $(PARSE_OBJ_PATH), $(PARSE_OBJ))
BUILT_OBJS	= $(addprefix $(BUILT_OBJ_PATH), $(BUILT_OBJ))
EXEC_OBJS	= $(addprefix $(EXEC_OBJ_PATH), $(EXEC_OBJ))

OBJECTS		= $(PARSE_OBJS) $(BUILT_OBJS) $(EXEC_OBJS)
OBJECT_PATHS= $(PARSE_OBJ_PATH) $(BUILT_OBJ_PATH) $(EXEC_OBJ_PATH) 

# ---------------- progress bar ------------------ #

# PRINTF_SIZE = $(shell ls libft/ft_printf/ | grep "\.c" | wc -l)
# GNL_SIZE = $(shell ls libft/gnl/ | grep "bonus.c" | wc -l)
# LIBFT_SIZE = $(shell ls libft/ | grep "\.c" | wc -l)
# ((TOTAL_LIBFT = $(PRINTF_SIZE) + $(GNL_SIZE) + $(LIBFT_SIZE))) <- fonctionne pas

# ------------------------------------------------ #

all: $(NAME)

$(OBJ_PATH) $(BUILT_OBJ_PATH) $(EXEC_OBJ_PATH) $(PARSE_OBJ_PATH):
	mkdir $(OBJ_PATH) $(PARSE_OBJ_PATH) $(BUILT_OBJ_PATH) $(EXEC_OBJ_PATH)

$(PARSE_OBJ_PATH)%.o:$(PARSE_PATH)%.c $(INC_FILES)
	$(CC) $(FLAGS) -c $< $ -I$(INC_PATH) -o $@

$(BUILT_OBJ_PATH)%.o:$(BUILT_PATH)%.c $(LIBFT) $(INC_FILES)
	$(CC) $(FLAGS) -c $< $ -I$(INC_PATH) -o $@

$(EXEC_OBJ_PATH)%.o:$(EXEC_PATH)%.c $(LIBFT) $(INC_FILES)
	$(CC) $(FLAGS) -c $< $ -I$(INC_PATH) -o $@

$(NAME): $(LIBFT) $(OBJECT_PATHS) $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) $(INCFLAGS) $(INC_PATH)minishell.h -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean:clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

run: $(NAME)
	clear
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all -s ./minishell

re: fclean all

.PHONY: all clean fclean re run

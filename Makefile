CC		= gcc
FLAGS	= -g3 #-Wall -Wextra -Werror
NAME	= minishell

LIBFT_PATH= libft/
LIBFT	= $(LIBFT_PATH)libft.a

OBJ_PATH= objs/
BUILT_OBJ_PATH= objs/builtins/
SRC_PATH= srcs/
BUILT_PATH= srcs/builtins/
INC_PATH= includes/

SRC		= check_init.c \
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
		

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
BUILTINS= $(addprefix $(BUILT_PATH), $(BUILTIN))
OBJ		= $(SRC:.c=.o)
BUILT_OBJ= $(BUILTIN:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
BUILT_OBJS= $(addprefix $(BUILT_OBJ_PATH), $(BUILT_OBJ))

# ---------------- progress bar ------------------ #

# PRINTF_SIZE = $(shell ls libft/ft_printf/ | grep "\.c" | wc -l)
# GNL_SIZE = $(shell ls libft/gnl/ | grep "bonus.c" | wc -l)
# LIBFT_SIZE = $(shell ls libft/ | grep "\.c" | wc -l)
# ((TOTAL_LIBFT = $(PRINTF_SIZE) + $(GNL_SIZE) + $(LIBFT_SIZE))) <- fonctionne pas

# ------------------------------------------------ #

all: $(NAME)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(BUILT_OBJ_PATH):
	mkdir $(BUILT_OBJ_PATH)

$(OBJ_PATH)%.o:$(SRC_PATH)%.c ./includes/minishell.h #$(INC_PATH)
	$(CC) $(FLAGS) -c $< -o $@

$(BUILT_OBJ_PATH)%.o:$(BUILT_PATH)%.c -I ./includes/
	$(CC) $(FLAGS) -c $< -o $@

# -I $(INC_PATH)

$(NAME): $(LIBFT) $(OBJ_PATH) $(BUILT_OBJ_PATH) $(OBJS) $(BUILT_OBJS)
	$(CC) $(FLAGS) $(OBJS) $(BUILT_OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean:clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

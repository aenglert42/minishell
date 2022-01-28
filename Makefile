CC = gcc

NAME = minishell

FLAGS = -g -Wall -Wextra -Werror

SRC_LIST =	1.0_tokenizer.c \
			1.1_tokenizer.c \
			1.2_tokenizer.c \
			2.0_expander.c \
			2.1_expander.c \
			2.2_expander.c \
			2.3_expander.c \
			3_quote_remove.c \
			4_parser_fst.c \
			4_parser_sec.c \
			4_parser_trd.c \
			4_parser_fth.c \
			4_syntaxcheck.c \
			utils1.c \
			utils2.c \
			utils3.c \
			5.0_executor.c \
			5.1_heredoc.c \
			5.2_childprocesses.c \
			5.3_redirect_std_fds.c \
			5.4_builtins_cd1.c \
			5.4_builtins_cd2.c \
			5.4_builtins_echo_env_exit_pwd.c \
			5.4_builtins_export_unset.c \
			5.4_builtins_utils.c \
			6_exit.c \
			6.1_free.c \
			7_signals.c\
			8_printstuff.c\
			main.c\
			debug.c \

LIBFT_PATH = ./libft/

MAKE = make

OBJS :=  $(SRC_LIST:.c=.o)

all: $(NAME)

$(NAME): sub_libft $(OBJS)
	@$(CC) $(FLAGS) -c $(SRC_LIST)
	@$(CC) $(FLAGS) $(OBJS) -lreadline $(LIBFT_PATH)libft.a -o $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

sub_libft:
	@$(MAKE) all libft.a -C $(LIBFT_PATH)

clean:
	@rm -f *.o
	@$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all
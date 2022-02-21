NAME := minishell
SRC_DIR := ./src/
OBJ_DIR := ./obj/
HEADER_DIR := ./inc/
SRCS :=	1.0_tokenizer.c \
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
		6.2_error.c \
		7_signals.c\
		8_printstuff.c\
		main.c
CC := gcc
CFLAGS := -g -Wall -Wextra -Werror
LINK := -I$(HEADER_DIR) -lreadline
OBJS := $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
HEADERS := $(HEADER_DIR)*.h
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
NC := \033[0m
LIBFT_DIR := ./libft/
LIBFT := $(LIBFT_DIR)libft.a
LIBFT_OBJS := $(LIBFT_DIR)obj/*.o
DEPS := $(HEADERS) $(LIBFT)
MAKE += --no-print-directory

all: link $(NAME)

link:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(OBJS) $(LINK) $(LIBFT) -o $@
	@echo "\n$(GREEN)$(NAME) created$(NC)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS) ofilemessage
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo ".\c"

ofilemessage:
	@echo "compiling $(NAME)-object-files: \c"

clean:
	@rm -rf $(OBJS) *.dSYM
	@echo "$(RED)$(NAME)-object-files deleted$(NC)"
	@echo "$(RED)$(NAME)-dSYM-files deleted$(NC)"
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(NC)"
	@$(MAKE) xclean -C $(LIBFT_DIR)

re: fclean all

peace:
	@echo "\n"
	@echo "     .''.    .',"
	@echo "     |  |   /  /"
	@echo "     |  |  /  /"
	@echo "     |  | /  /"
	@echo "     |  |/  ;-._"
	@echo "     }  \` _/  / ;"
	@echo "     |  /\` ) /  /"
	@echo "     | /  /_/\_/\ "
	@echo "     |/  /      |"
	@echo "     (  ' \ '-  |"
	@echo "      \    \`.  /"
	@echo "       |      |"
	@echo "       |      |\n"

.INTERMEDIATE: ofilemessage

.PHONY: clean fclean all re
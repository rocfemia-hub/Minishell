NAME = minishell
CC = cc
CCFLAGS = -g3 -Wall -Wextra -Werror #-fsanitize=address

BLUE = \033[34m
RESET = \033[0m

SRC = mix/list.c mix/main.c mix/error.c mix/free.c mix/split_mini.c mix/signals.c\
      exec/built_ins1.c exec/built_ins2.c exec/builtins_utils1.c exec/builtins_utils2.c exec/builtins_utils3.c exec/exec_control.c exec/executor.c exec/heredoc.c exec/pids.c exec/pipelines.c exec/redirections.c\
      parser/token.c parser/aux_token.c parser/quotes.c parser/keep_quotes.c parser/utils_quotes.c parser/struct.c parser/expander_cmd.c parser/expander_args.c parser/aux_expander.c parser/utils_expander.c parser/redirects.c parser/utils_redirects.c parser/ft_split_parser.c parser/redirects_cmd.c parser/syntax_validator.c \

OBJS = ${SRC:.c=.o}

INCLUDES = -I. -Ilibft
LIBFTA = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	@$(CC) $(CCFLAGS) $(OBJS) $(LIBFTA) -lreadline -lhistory -o $(NAME)
	@echo "$(BLUE)||>> minishell compiled!! <<||$(RESET)"

mix/%.o: mix/%.c
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

exec/%.o: exec/%.c
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

parser/%.o: parser/%.c
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re

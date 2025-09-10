NAME = minishell
CC = cc
CCFLAGS = -g3 -fsanitize=address #-Wall -Wextra -Werror

BLUE = \033[34m
RESET = \033[0m

SRC = mix/list.c mix/main.c mix/error.c mix/free.c\
      exec/built_ins1.c exec/built_ins2.c exec/executor.c exec/utils_built_ins1.c exec/utils_built_ins2.c exec/redirections.c\
      parser/token.c parser/split_mini.c parser/quotes.c parser/struct.c parser/expander.c parser/redirects.c\

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
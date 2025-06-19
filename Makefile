NAME = minishell
CC = cc
CCFLAGS = #-Wall -Wextra -Werror -g3

BLUE = \033[34m
RESET = \033[0m

SRC = mix/main.c exec/built_ins.c parser/parser.c
OBJ = mix/main.o exec/built_ins.o

INCLUDES = -I. -IHelicopter

LIBFTA = Helicopter/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C Helicopter
	@$(CC) $(CCFLAGS) $(OBJ) $(LIBFTA) -lreadline -lhistory -o $(NAME)
	@echo "$(BLUE)||>> minishell compiled!! <<||$(RESET)"

mix/%.o: mix/%.c
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

exec/%.o: exec/%.c
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C Helicopter clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C Helicopter fclean

re: fclean all

.PHONY: all clean fclean re

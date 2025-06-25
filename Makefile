NAME = minishell
CC = cc
CCFLAGS = -fsanitize=address -g3 #-Wall -Wextra -Werror -g3

BLUE = \033[34m
RESET = \033[0m

SRC = mix/listas.c mix/main.c mix/error.c exec/built_ins.c exec/utils_built_ins.c parser/token.c parser/split_mini.c parser/commands1.c parser/commands2.c 
OBJ = mix/listas.o mix/main.o mix/error.o exec/built_ins.o exec/utils_built_ins.o parser/token.o parser/split_mini.o parser/commands1.o parser/commands2.o 

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

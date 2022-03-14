NAME = philo

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/

SRC = philo_main.c\
		atoi_philo.c\
		ft_memset.c\
		ft_strjoin.c\
		ft_strlen.c\
		process_argv.c\
		test_prints.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INC = $(addprefix -I, $(INC_DIR))

CC = gcc
CFLAG = -Werror -Wall -Wextra -g3 -fsanitize=address -MD
CFLAG = -Werror -Wall -Wextra -g3 -MD
RM = rm -rf

.PHONY: fclean all clean re

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAG) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $^ -o $@ $(INC) -lpthread

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(OBJ_DIR)/*.d

NAME = philo_bonus

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/

SRC =	main.c\
		atoi_philo.c\
		check_num_loops.c\
		libft_functions.c\
		philo_cycle.c\
		print_msg.c\
		process_argv.c\
		send_check_lives.c\
		send_check_num_loops.c\
		send_get_time.c\
		send_start_philos.c\
		set_philo_args.c\
		set_processes.c\
		set_semaphores.c\
		timer.c\

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INC = $(addprefix -I, $(INC_DIR))

CC = gcc
#CFLAG = -Werror -Wall -Wextra -g3 -fsanitize=address
CFLAG = -Werror -Wall -Wextra -g3
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

re: fclean
	$(MAKE)

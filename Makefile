NAME = philo

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/

SRC =	main.c\
		atoi_philo.c\
		frees.c\
		libft_functions.c\
		philo_cycle.c\
		print_msg.c\
		process_argv.c\
		send_check_lives.c\
		send_start_philos.c\
		set_forks.c\
		set_threads.c\
		timer.c\
		test_prints.c
		#check_death.c\
		check_life.c\
		log.c\
		log_print.c\
		log_search_min.c\
		philo_main.c\
		philo_step.c\
		send_log.c\
		send_printing_queue.c\
		set_local_queue_args.c\
		set_philo_args.c\
		set_queue_args.c\
		thread_functions.c\
		thread_philo.c\

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

-include $(OBJ_DIR)/*.d

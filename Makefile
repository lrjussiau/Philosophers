# Compiler and compiling flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Name of the target executable
NAME = philo

# Source and object files
SRCS = getters_setters.c main.c parsing.c safe_func.c synchro_utils.c write.c init_data.c monitor.c simulation.c utils.c
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = philo.h

# Rule to make everything
all: $(NAME)

# Rule to compile the program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Rule to compile object files from source files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean object files
clean:
	rm -f $(OBJS)

# Rule to full clean (clean + remove executable)
fclean: clean
	rm -f $(NAME)

# Rule to re-make everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re

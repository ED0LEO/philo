SRC = main.c clean.c initialize.c monitoring.c phil_utils.c start.c forks.c ft_atoi.c phil_life.c
OBJS = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)
CC = gcc

CFLAGS  = -Wall -Wextra -Werror -MMD

TARGET = philo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.PHONY: clean fclean all re

-include $(DEPS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
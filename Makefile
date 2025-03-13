# Colors must be included in the form of codes. NC = No color
GREEN = \033[0;32m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
YELLOW = \033[0;33m
NC = \033[0m

SOURCES = client.c \
          server.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: server client

bonus: server client

server: server.o libft
	@echo -e "$(CYAN)Compiling Server.$(NC)"
	@$(CC) -o $@ $< -Llibft -lft

client: client.o libft
	@echo -e "$(CYAN)Compiling Client.$(NC)"
	@$(CC) -o $@ $< -Llibft -lft

libft:
	@make -C libft

clean:
	@echo -e "$(YELLOW)Removing .o files.$(NC)"
	@rm -f $(OBJECTS)
	@make -C libft clean

fclean: clean
	@echo -e "$(YELLOW)Removing executables.$(NC)"
	@rm -f server client libft/libft.a

re: fclean all

%.o: %.c
	@$(CC) -c $(CFLAGS) $?


.PHONY: all bonus libft clean fclean re

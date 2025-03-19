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

libft/libft.a:
	@$(MAKE) -C libft

server: server.o libft/libft.a
	@echo -e "$(CYAN)Compiling Server.$(NC)"
	@$(CC) $(CFLAGS) -o $@ server.o -Llibft -lft

client: client.o libft/libft.a
	@echo -e "$(CYAN)Compiling Client.$(NC)"
	@$(CC) $(CFLAGS) -o $@ client.o -Llibft -lft

clean:
	@echo -e "$(YELLOW)Removing .o files.$(NC)"
	@rm -f $(OBJECTS)
	@$(MAKE) -C libft clean

fclean: clean
	@echo -e "$(YELLOW)Removing executables.$(NC)"
	@rm -f server client libft/libft.a

re: fclean all

%.o: %.c
	@$(CC) -c $(CFLAGS) $?


.PHONY: all bonus clean fclean re

#Ubuntu use echo without -e, Fedora must use -e

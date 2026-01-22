.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror

CLIENT_NAME = client
SERVER_NAME = server
LIBFT = ./libft/libft.a

MAKE = make

CLIENT_SRCS = client.c
SERVER_SRCS = server.c

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

all: $(LIBFT) $(SERVER_NAME) $(CLIENT_NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS)  -o $@ $^ $(LIBFT)

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS)  -o $@ $^ $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
	$(MAKE) -C ./libft fclean
re: fclean all


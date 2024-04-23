CC = gcc
CFLAGS = -Wall -Wextra -Werror
C_PRECOMPILE_FLAGS = -c
C_DEBUG_FLAG = -g

LIBFT_DIR = ./libft
LIBFT_NAME = libdmoroz.a
LIBFT = $(addprefix $(LIBFT_DIR)/, $(LIBFT_NAME))

SERVER_NAME = server
SERVER_SRCS = server.c \
			  server_cycle.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
SERVER_INCS = server.h \
			  common.h \
			  $(LIBFT_DIR)/libft/libft.h \
			  $(LIBFT_DIR)/ftprintf/ft_printf.h
SERVER_INCS_DIR = $(dir $(SERVER_INCS))
SERVER_INC_FLAGS = $(addprefix -I, $(SERVER_INCS_DIR))

CLIENT_NAME = client
CLIENT_SRCS = client.c \
			  client_send_data.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CLIENT_INCS = client.h \
			  common.h \
			  $(LIBFT_DIR)/libft/libft.h \
			  $(LIBFT_DIR)/ftprintf/ft_printf.h
CLIENT_INCS_DIR = $(dir $(CLIENT_INCS))
CLIENT_INC_FLAGS = $(addprefix -I, $(CLIENT_INCS_DIR))


LIB_FLAGS = -L$(LIBFT_DIR)/ -ldmoroz

all: $(SERVER_NAME) $(CLIENT_NAME)

%.o: %.c $(SERVER_INCS) $(CLIENT_INCS)
	$(CC) $(CFLAGS) $(C_PRECOMPILE_FLAGS) $(SERVER_INC_FLAGS) $(CLIENT_INC_FLAGS) $(LIB_FLAGS) $< -o $@ 

$(SERVER_NAME): $(LIBFT) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_INC_FLAGS) $(SERVER_OBJS) $(LIB_FLAGS) -o $(SERVER_NAME)

$(CLIENT_NAME): $(LIBFT) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_INC_FLAGS) $(CLIENT_OBJS) $(LIB_FLAGS) -o $(CLIENT_NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(SERVER_OBJS)
	rm -f $(CLIENT_OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(SERVER_NAME)
	rm -f $(CLIENT_NAME)

re: fclean all

bonus: all

$(LIBFT):
	$(MAKE) all bonus clean -C $(LIBFT_DIR)

.PHONY: all clean fclean re bonus
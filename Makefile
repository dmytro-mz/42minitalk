CC = gcc
CFLAGS = -Wall -Wextra -Werror
C_PRECOMPILE_FLAGS = -c
C_DEBUG_FLAG = -g

LIBFT_DIR = ./libft
LIBFT_NAME = libdmoroz.a
LIBFT = $(addprefix $(LIBFT_DIR)/, $(LIBFT_NAME))

SERVER_NAME = server
SERVER_SRCS = server.c
SERVER_OBJS = $(SRCS:.c=.o)
SERVER_INCS = server.h \
       $(LIBFT_DIR)/libft/libft.h \
       $(LIBFT_DIR)/ftprintf/ft_printf.h \
       $(LIBFT_DIR)/ftgnl/get_next_line_bonus.h
SERVER_INCS_DIR = $(dir $(SERVER_INCS))
SERVER_INC_FLAGS = $(addprefix -I, $(SERVER_INCS_DIR))

CLIENT_NAME = client
CLIENT_SRCS = client.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CLIENT_INCS = client.h \
       $(LIBFT_DIR)/libft/libft.h \
       $(LIBFT_DIR)/ftprintf/ft_printf.h \
       $(LIBFT_DIR)/ftgnl/get_next_line_bonus.h
CLIENT_INCS_DIR = $(dir $(CLIENT_INCS))
CLIENT_INC_FLAGS = $(addprefix -I, $(CLIENT_INCS_DIR))


LIB_FLAGS = -L$(LIBFT_DIR)/ -ldmoroz

all: $(SERVER_NAME) $(CLIENT_NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) $(C_PRECOMPILE_FLAGS) $(INC_FLAGS) $(LIB_FLAGS) $< -o $@ 

$(SERVER_NAME): $(LIBFT) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_INC_FLAGS) $(SERVER_OBJS) $(LIB_FLAGS) -o $(SERVER_NAME)

$(SERVER_NAME): $(LIBFT) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_INC_FLAGS) $(SERVER_OBJS) $(LIB_FLAGS) -o $(SERVER_NAME)

debug: $(LIBFT)
	$(CC) $(CFLAGS) $(C_DEBUG_FLAG) $(INC_FLAGS) $(SRCS) $(LIB_FLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(INC_FLAGS) $(LIB_FLAGS) -o $(BONUS_NAME)

$(LIBFT):
	$(MAKE) all bonus clean -C $(LIBFT_DIR)

.PHONY: all clean fclean re bonus
.DEFAULT_GOAL := all
applications := client servrer

GREEN := \033[1;92m
DEFAULT := \033[1;39m

# commands
CC := cc
FLAGS = -Wall -Wextra -Werror
RM =rm -f

# headers
HEADERS = -I. -Ilibft/include

# libft
LIBFT_DIR = libft
LIBFT := $(LIBFT_DIR)/libft.a
LBFLAGS := -L$(LIBFT_DIR) -lft

# srcs
CLIENT_SRC = client.c utils.c
SERVER_SRC = server.c utils.c

# objs
OBJS_DIR := ./obj
CLIENT_OBJS = $(CLIENT_SRC:%.c=$(OBJS_DIR)/%.o)
SERVER_OBJS = $(SERVER_SRC;%.c=$(OBJS_DIR)/%.o)



$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@
	@echo "$(GREEN)Compiling: $(notdir $<)$(DEFAULT)"

client: $(LIBFT) $(CLIENT_OBJS)
	@$(CC) $(FLAGS) $(LBFLAGS) $(CLIENT_OBJS) $(LIBFT) -o $@
	@echo "$(GREEN)Client has been generated!$(DEFAULT)"

server: $(LIBFT) $(SERVER_OBJS)
	@$(CC) $(FLAGS) $(LBFLAGS) $(SERVER_OBJS) $(LIBFT) -o $@
	@echo "$(GREEN)Server has been generated!$(DEFAULT)"

all: $(applications)

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(CLIENT_OBJS) $(SERVER_OBJS)
	@rmdir $(OBJS_DIR) 2> /dev/null || true
	@echo "$(GREEN)OBJS are cleaned!$(DEFAULT)"

fcean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(applications)

re: fclean all

.PHONY clean fclean re all

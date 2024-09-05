.DEFAULT_GOAL := all
applications := client server
applications_bonus := client_bonus server_bonus

GREEN := \033[1;92m
DEFAULT := \033[1;39m

#---------------------------------------------------------------------------------------------------------

# commands
CC := cc
FLAGS := -Wall -Wextra -Werror
RM :=rm -f

# headers
HEADERS = -I. -Ilibft/include

# libft
LIBFT_DIR = libft
LIBFT := $(LIBFT_DIR)/libft.a
#LBFLAGS := -L$(LIBFT_DIR) -lft

#---------------------------------------------------------------------------------------------------------

# srcs
CLIENT_SRC = client.c utils.c
SERVER_SRC = server.c utils.c

# objs
CLIENT_OBJS = $(CLIENT_SRC:%.c=%.o)
SERVER_OBJS = $(SERVER_SRC:%.c=%.o)

#---------------------------------------------------------------------------------------------------------

# bonus srcs
BONUS_CLIENT_SRC = bonus/client_bonus.c bonus/utils_bonus.c
BONUS_SERVER_SRC = bonus/server_bonus.c bonus/utils_bonus.c

# bonus objs
BONUS_CLIENT_OBJS = $(BONUS_CLIENT_SRC:%.c=%.o)
BONUS_SERVER_OBJS = $(BONUS_SERVER_SRC:%.c=%.o)

#---------------------------------------------------------------------------------------------------------

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@
	@echo "Compiling: $(notdir $<)"

client: $(LIBFT) $(CLIENT_OBJS)
	@$(CC) $(FLAGS) $(CLIENT_OBJS) $(LIBFT) -o $@
	@echo "$(GREEN)Client has been generated!$(DEFAULT)"

server: $(LIBFT) $(SERVER_OBJS)
	@$(CC) $(FLAGS) $(SERVER_OBJS) $(LIBFT) -o $@
	@echo "$(GREEN)Server has been generated!$(DEFAULT)"

all: $(applications)

#---------------------------------------------BONUS-------------------------------------------------------

client_bonus: $(LIBFT) $(BONUS_CLIENT_OBJS)
	@$(CC) $(FLAGS) $(LIBFT) $(BONUS_CLIENT_OBJS) -o $@
	@echo "$(GREEN)Client_bonus has been generated!"$(DEFAULT)"

server_bonus: $(LIBFT) $(BONUS_SERVER_OBJS)
	@$(CC) $(FLAGS) $(LIBFT) $(BONUS_SERVER_OBJS) -o $@
	@echo "$(GREEN)Server_bonus has been generated!"$(DEFAULT)"

bonus: .bonus
.bonus: $(applications_bonus)

#---------------------------------------------------------------------------------------------------------

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(CLIENT_OBJS) $(SERVER_OBJS) $(BONUS_CLIENT_OBJS) $(BONUS_SERVER_OBJS)
	@rmdir $(OBJS_DIR) 2> /dev/null || true
	@rmdir $(BONUS_OBJS_DIR) 2> /dev/null || true
	@$(RM) .bonus
	@echo "$(GREEN)OBJS are cleaned!$(DEFAULT)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(applications) $(applications_bonus)
	@echo "$(GREEN)Files are cleaned.$(DEFAULT)"

re: fclean all

.PHONY: clean fclean re all bonus

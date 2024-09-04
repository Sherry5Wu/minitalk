GREEN = \033[1;92m
DEFAULT = \033[0;39m

NAME = libft.a

AR     := ar -rc
RM     := rm -f
CC     := cc
CFLAGS = -Wall -Wextra -Werror

SRCS   := ./convert/ft_atoi.c \
		  ./convert/ft_itoa.c \
		  ./convert/ft_tolower.c \
		  ./convert/ft_toupper.c \
		  ./ctype/ft_isalpha.c \
		  ./ctype/ft_isdigit.c \
		  ./ctype/ft_isalnum.c \
		  ./ctype/ft_isascii.c \
		  ./ctype/ft_isprint.c \
		  ./io/ft_putchar_fd.c \
		  ./io/ft_putstr_fd.c \
		  ./io/ft_putendl_fd.c \
		  ./io/ft_putnbr_fd.c \
		  ./list/ft_lstnew.c \
		  ./list/ft_lstadd_front.c \
		  ./list/ft_lstsize.c \
		  ./list/ft_lstlast.c \
		  ./list/ft_lstadd_back.c \
		  ./list/ft_lstdelone.c \
		  ./list/ft_lstclear.c \
		  ./list/ft_lstiter.c \
		  ./list/ft_lstmap.c \
		  ./mem/ft_memset.c \
		  ./mem/ft_memcpy.c \
		  ./mem/ft_memmove.c \
		  ./mem/ft_memchr.c \
		  ./mem/ft_memcmp.c \
		  ./str/ft_strlen.c \
		  ./str/ft_bzero.c \
		  ./str/ft_strlcpy.c \
		  ./str/ft_strlcat.c \
		  ./str/ft_strchr.c \
		  ./str/ft_strrchr.c \
		  ./str/ft_strncmp.c \
		  ./str/ft_strnstr.c \
		  ./str/ft_calloc.c \
		  ./str/ft_strdup.c \
		  ./str/ft_substr.c \
		  ./str/ft_strjoin.c \
		  ./str/ft_strtrim.c \
		  ./str/ft_split.c \
		  ./str/ft_strmapi.c \
		  ./str/ft_striteri.c \
		  ./ft_printf/ft_output.c \
		  ./ft_printf/ft_printf.c
OBJS   = $(SRCS:.c=.o)

HEADER := -I./include


all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "$(GREEN)libft.a compiled!$(DEFAULT)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADER) -fPIC -c $< -o $@
	@echo "Compiling: $<"

clean:
	@$(RM) $(OBJS)
	@echo "$(GREEN)Libft object files are cleaned!$(DEFAULT)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Libft library file is cleaned!$(DEFAULT)"

re:	fclean all

.PHONY:		all clean fclean re

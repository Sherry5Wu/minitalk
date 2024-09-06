#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <sys/types.h>
//# include <unistd.h>
//# include <stdlib.h>
# include <stdbool.h>
# include "./libft/include/libft.h"
# include "./libft/include/ft_printf.h"

# define TIMEOUT_MICROSECOND (100000)

typedef struct s_client
{
	int		singal;
	pid_t	pid;
}	t_client;

void	exit_msg(char *message);

#endif

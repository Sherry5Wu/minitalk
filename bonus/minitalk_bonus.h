/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:53:07 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/09 11:15:25 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <sys/types.h>
# include <stdbool.h>
# include "libft.h"
# include "ft_printf.h"

# define TIMEOUT_MICROSECOND (10000000)

typedef struct s_client
{
	int		singal;
	pid_t	pid;
}	t_client;

void	exit_msg(char *message);

#endif

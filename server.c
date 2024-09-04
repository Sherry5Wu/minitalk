/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:02:00 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/04 09:44:05 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int signum)
{
	static int32_t	bit;
	static int32_t	c;

	bit = 0;
	c = 0;
	if (signum == SIGUSR1)
		c |= (0x01 << bit);
	else if (signum == SIGUSR2)
		c |= (0x00 << bit);
	if (bit == 7)
	{
		ft_printf("%c", c);
		bit = 0;
		c = 0;
	}
	bit++;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) !=0)
		exit_msg("Failed to empty the set.");
	if (sigaddset(&sa.sa_mask, SIGUSR1) == -1 ||
		sigaddset(&sa.sa_mask, SIGUSR2))
		exit_msg("Failed to add signal to set.");
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		ft_printf("Waiting for a new connection. Listening...\n");
		if(sigaction(SIGUSR1, &sa, NULL) == -1);
			exit_msg("Fail to handle signal!");
		if(sigaction(SIGUSR2, &sa, NULL) == -1)
			exit_msg("Fail to handle signal!");
	}
}

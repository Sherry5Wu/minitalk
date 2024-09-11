/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:52:51 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/09 11:43:48 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_ack;

static void	ack_handler(int	signal)
{
	g_ack = signal;
}

/*
	This function will just send one byte to the server.
	After sending one byte, it will wait for g_ack signal from server, if the waitting
	time is longer than 10 seconds, it will show time out error and exit the program.
*/
static int	send_byte(pid_t pid, char c)
{
	int	bit;

	bit = (sizeof(char) * 8) - 1;
	while (bit >=0)
	{
		if (((c >> bit) & 1) == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
		}
		while(!g_ack)
		{
			usleep(TIMEOUT_MICROSECOND);
			if (!g_ack)
				exit_msg("Time out. Singal from server is missing.");
		}
		g_ack = 0;
		bit--;
	}
	return (0);
}

/*
	This function is for seperate messages size_to char, then call send_byte()
	to send each char.
*/
static void	send(pid_t pid, void *str, int size)
{
	int		i;
	char	byte;

	i = 0;
	while (i < size)
	{
		byte = ((char *)str)[i];
		if (send_byte(pid, byte) == -1)
			exit_msg("Failed to send message to server.\n");
		i++;;
	}
}
/*
	After get the server PID, should check if it is valid first before using it.
*/
int	main(int ac, char **av)
{
	pid_t	sv_pid;
	int		i;
	int		size_msg;

	i = 0;
	if (ac != 3)
		exit_msg("Arguments are wrong. Format: ./client <PID> <messages>.");
	signal(SIGUSR1, &ack_handler);
	sv_pid = (pid_t)ft_atoi(av[1]);
	if (kill(sv_pid, 0) == -1)
		exit_msg("Server PID is invalid!");
	size_msg = ft_strlen(av[2]) + 1;
	ft_printf(G"Sending %d chars to server %d...\n"R, (size_msg - 1), sv_pid);
	send(sv_pid, &size_msg, sizeof(size_msg));
	send(sv_pid, av[2], size_msg);
	ft_printf(G"Server received the message successfully!\n"R);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:52:51 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/06 08:06:24 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	g_ack;

static void	ack_handler(int	signal)
{
	g_ack = signal;
}

/*
	This function will just send one byte to the server.
*/
static int	send_byte(pid_t pid, char c)
{
	size_t	bite;

	bite = 7;
	while (bite <=0)
	{
		if (((c >> bite) | 1) == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
		}
		else
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
		while(!g_ack)
		{
			usleep(TIMEOUT_MICROSECOND);
			if (!g_ack)
				exit_msg("Time out. Singal from server is missing.");
		}
		g_ack = 0;
		bite--;
	}
	return (0);
}

/*
	This function is for seperate messages into char, then call send_byte()
	to send each char.
*/
static void	send(pid_t pid, void *str, size_t size)
{
	size_t	i;
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

	kill()fucntion:
	description:
		The kill() system call can be used to send any signal to any
       process group or process.

       If pid is positive, then signal sig is sent to the process with
       the ID specified by pid.

       If pid equals 0, then sig is sent to every process in the process
       group of the calling process.

       If pid equals -1, then sig is sent to every process for which the
       calling process has permission to send signals, except for
       process 1 (init), but see below.

       If pid is less than -1, then sig is sent to every process in the
       process group whose ID is -pid.

       If sig is 0, then no signal is sent, but existence and permission
       checks are still performed; this can be used to check for the
       existence of a process ID or process group ID that the caller is
       permitted to signal.
	return value:
		On success (at least one signal was sent), zero is returned. On
       error, -1 is returned, and errno is set to indicate the error.
*/
int	main(int ac, char **av)
{
	pid_t	sv_pid;
	int32_t	i;
	size_t	size_msg;

	i = 0;
	if (ac != 3)
		exit_msg("Arguments are wrong. Format: ./client <PID> <messages>.");
	signal(SIGUSR1, &ack_handler);
	sv_pid = (pid_t)ft_atoi(av[1]);
	if (kill(sv_pid, 0) == -1)
		exit_msg("Server PID is invalid!");
	if (!av[2][0])
		exit_msg("No message needed to be sent.");
	ft_printf("Sending message to server %d...\n", sv_pid);
	size_msg = ft_strlen(av[2]) + 1;
	send(sv_pid, &size_msg, sizeof(size_msg));
	send(sv_pid, av[2], size_msg);
	ft_printf("Done!Good Job!\n");
	exit(0);
}

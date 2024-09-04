/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:52:51 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/04 14:42:23 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_msg(pid_t pid, char c)
{
	int32_t	bit;

	bit = 7;
	while (bit <= 0)
	{
		if (c >> bit & 1 == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		usleep(100);
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
		On success (at least one signal was sent), zero is returned.  On
       error, -1 is returned, and errno is set to indicate the error.
*/
int	main(int ac, char **av)
{
	pid_t		sv_pid;
	int32_t		i;
	uint32_t	len_msg;

	i = 0;
	if (ac != 3)
		ft_printf("Arguments are wrong. Format: ./client <PID> <messages>.");
	else
	{
		sv_pid = (pid_t)ft_atoi(av[1]);
		if (kill(sv_pid, 0) == -1)
			exit_msg("Server PID is invalid!");
		if (!av[2][0])
			exit_msg("No message needed to be sent.");
		ft_printf("Sending message to server %d...\n", sv_pid);
		len_msg = ft_strlen(av[2]) + 1;
		while (av[2][i])
		{
			send_msg(sv_pid, av[2][i]);
			i++;
		}
		send_msg(sv_pid, '\n');
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:02:00 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/05 13:47:52 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client	g_client;

static int	receive_byte(void)
{
	int	byte;
	int	bite;

	byte = 0;
	bite = 7;
	while (bite >= 0)
	{
		while (!g_client.singal)
		{
			usleep(TIMEOUT_MICROSECOND);
			if (!g_client.singal)
				return (-1);
		}
		if (g_client.singal == SIGUSR1)
			byte |= 1 << bite;
		bite--;
		g_client.singal = 0;
		kill(g_client.pid, SIGUSR1);
	}
	return (byte);
}

static bool	receive_msg(void *str, size_t size)
{
	size_t	i;
	int		receive_char;

	ft_bzero(str, size);
	i = 0;
	while (i < size)
	{
		receive_char = receive_byte();
		if (receive_char == -1)
			return (false);
		((char *)str)[i] = receive_char;
		i++;
	}
	return (true);
}

static void	print_msg(size_t size)
{
	char	*message;

	message = malloc(sizeof(char) * size);
	if (!message)
		exit_msg("Failed to malloc the message.");
	message[size - 1] = '\0';
	if (receive_msg(message, size) == true)
	{
		ft_printf("The size of message is %d\n", (size - 1));
		ft_printf("%s\n", message);
	}
	else
		ft_printf("Timeout. The client's signal may be missing.\n");
	free(message);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_client.pid == 0)
		g_client.pid = info->si_pid;
	if (g_client.pid == info->si_pid)
		g_client.singal = signum;
}

int	main(void)
{
	struct sigaction	action;
	size_t				size_msg;
	bool				flag_msg;

	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	// Initialize signal set to empty
	if (sigemptyset(&action.sa_mask) !=0)
		exit_msg("Failed to empty the set.");
	// if (sigaddset(&action.sa_mask, SIGUSR1) < 0 ||
	// 	sigaddset(&action.sa_mask, SIGUSR2) < 0)
	// 	exit_msg("Failed to add signal to set.");
	if(sigaction(SIGUSR1, &action, NULL) < 0 ||
		sigaction(SIGUSR2, &action, NULL) < 0)
			exit_msg("Fail to handle signal!");
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		g_client.pid = 0;
		ft_printf("Waiting for a new connection. Listening...\n");
		size_msg = 0;
		flag_msg = receive_msg(&size_msg, sizeof(size_msg));
		if (flag_msg == true && size_msg)
			print_msg(size_msg);
	}
}

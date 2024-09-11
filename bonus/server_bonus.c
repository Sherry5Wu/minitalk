/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:02:00 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/06 11:52:41 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	receive_byte(void)
{
	int	byte;
	int	bit;

	byte = 0;
	bit = (sizeof(char) * 8) - 1;
	while (bit >= 0)
	{
		while (!g_client()->singal)
		{
			usleep(TIMEOUT_MICROSECOND);
			if (!g_client()->singal)
				return (-1);
		}
		if (g_client()->singal == SIGUSR1)
			byte |= 1 << bit;
		bit--;
		g_client()->singal = 0;
		kill(g_client()->pid, SIGUSR1);
	}
	return (byte);
}

static bool	receive_msg(void *str, int size)
{
	int	i;
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

/*
	This function will receive the message(receive them in a str), then print the string out.
*/
static void	receive_print_msg(int size)
{
	char	*message;

	message = (char *)malloc(sizeof(char) * size);
	if (!message)
		exit_msg("Failed to malloc the message.");
	message[size - 1] = '\0';
	if (receive_msg(message, size) == true)
	{
		ft_printf(G"Recevied %d chars from a client.\n"R, (size - 1));
		ft_printf("%s\n", message);
	}
	else
		ft_printf(RD"Timeout. The client's signal may be missing.\n"R);
	free(message);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_client()->pid == 0)
		g_client()->pid = info->si_pid;
	if (g_client()->pid == info->si_pid)
		g_client()->singal = signum;
}

int	main(void)
{
	struct sigaction	action;
	int				size_msg;
	bool				flag_msg;

	action.sa_sigaction = &signal_handler;
	action.sa_flags = SA_SIGINFO;
	// Initialize signal set to empty
	if (sigemptyset(&action.sa_mask) !=0)
		exit_msg("Failed to empty the set.");
	if (sigaddset(&action.sa_mask, SIGUSR1) < 0 ||
		sigaddset(&action.sa_mask, SIGUSR2) < 0)
		exit_msg("Failed to add signal to set.");
	if(sigaction(SIGUSR1, &action, NULL) < 0 ||
		sigaction(SIGUSR2, &action, NULL) < 0)
			exit_msg("Fail to handle signal!");
	ft_printf(G"Server PID: %d\n"R, getpid());
	while (1)
	{
		g_client()->pid = 0;
		size_msg = 0;
		flag_msg = receive_msg(&size_msg, sizeof(size_msg));
		if (flag_msg == true && size_msg)
			receive_print_msg(size_msg);
	}
}

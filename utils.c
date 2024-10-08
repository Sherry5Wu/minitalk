/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:37:45 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/04 08:38:00 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_msg(char *message)
{
	if (message)
	{
		ft_printf("%s\n", message);
	}
	exit(1);
}

t_client	*g_client(void)
{
	static t_client		g_client;

	return (&g_client);
}

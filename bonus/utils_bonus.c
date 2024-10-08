/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:37:45 by jingwu            #+#    #+#             */
/*   Updated: 2024/09/06 11:52:51 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	exit_msg(char *message)
{
	if (message)
	{
		ft_printf(RD"%s\n"R, message);
	}
	exit(1);
}

t_client	*g_client(void)
{
	static t_client		g_client;

	return (&g_client);
}

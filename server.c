/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:23:02 by ahhammad          #+#    #+#             */
/*   Updated: 2026/01/23 14:43:08 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "./libft/libft.h"

char	*g_msg;

void	handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c[2];
	static int				i;

	(void) context;
	c[1] = '\0';
	c[0] = c[0] << 1;
	if (sig == SIGUSR1)
		c[0] = c[0] | 1;
	i++;
	if (i == 8)
	{
		if (c[0] == '\0')
		{
			g_msg = ft_strjoin(g_msg, (char *)c);
			ft_putstr_fd(g_msg, 1);
			free(g_msg);
			g_msg = NULL;
		}
		else
			g_msg = ft_strjoin(g_msg, (char *)c);
		c[0] = '\0';
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	segment;

	g_msg = ft_itoa(getpid());
	ft_putendl_fd(g_msg, 1);
	free(g_msg);
	g_msg = NULL;
	segment.sa_sigaction = handler;
	segment.sa_flags = SA_SIGINFO ;
	sigemptyset(&segment.sa_mask);
	sigaction(SIGUSR1, &segment, NULL);
	sigaction(SIGUSR2, &segment, NULL);
	while (1)
		;
	return (0);
}

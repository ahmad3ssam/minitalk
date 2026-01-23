/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:10:16 by ahhammad          #+#    #+#             */
/*   Updated: 2026/01/23 14:21:41 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "./libft/libft.h"

int	g_ack;

void	ack_handler(int sig)
{
	(void) sig;
	g_ack = 1;
}

void	send_bits(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_ack = 0;
		if (((c >> i) & 1) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		while (g_ack == 0)
			;
	}
}

void	send_message(int pid, char *message)
{
	int	i;

	if (!message)
		return ;
	i = 0;
	while (message[i])
	{
		send_bits(pid, message[i]);
		i++;
	}
	if (message[i] == '\0')
		send_bits(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		return (0);
	pid = ft_atoi(argv[1]);
	if (kill (pid, 0) == -1)
	{
		write(1, "Invalid PID\n", 13);
		return (-1);
	}
	signal(SIGUSR1, ack_handler);
	send_message(pid, argv[2]);
	return (0);
}

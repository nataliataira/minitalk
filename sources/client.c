/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:09:51 by ngomes-t          #+#    #+#             */
/*   Updated: 2023/01/18 03:23:26 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_signal;

static void	sig_rcv(int signal)
{
	if (signal == SIGUSR1)
		g_signal = 0;
	else
		ft_putendl_fd("The message has been sent to the server .", 1);
}

void	error_message(char *message)
{
	ft_putendl_fd(message, 1);
	exit(1);
}

static void	send_message(int pid, char c)
{
	int	shifted;

	shifted = 0;
	while (shifted < 8)
	{
		if (g_signal == 0)
		{
			g_signal = 1;
			if (c >> shifted & 0b00000001)
			{
				if (kill(pid, SIGUSR1))
					error_message("Unable to send signal .");
			}
			else
			{
				if (kill(pid, SIGUSR2))
					error_message("Unable to send signal .");
			}
			shifted++;
		}
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	action;
	char				*message;
	int					pid;
	int					c;

	if (argc != 3)
		error_message("Usage: ./client 'PID' 'Message' .");
	g_signal = 0;
	c = 0;
	pid = ft_atoi(argv[1]);
	message = argv[2];
	ft_bzero(&action, sizeof (struct sigaction));
	action.sa_handler = &sig_rcv;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (message[c])
		send_message(pid, message[c++]);
	send_message(pid, '\n');
	send_message(pid, '\0');
	usleep(100);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:09:57 by ngomes-t          #+#    #+#             */
/*   Updated: 2023/01/18 03:23:23 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	error_message(char *message)
{
	ft_putendl_fd(message, 1);
	exit(1);
}

static void	print_message(int signal, siginfo_t *info, void *ucontext)
{
	static int	shifted;
	static char	letter;

	(void)ucontext;
	if (signal == SIGUSR1)
		letter += (0b00000001 << shifted);
	if (shifted == 7)
	{
		if (letter)
			ft_putchar_fd(letter, 1);
		else
		{
			if (kill(info->si_pid, SIGUSR2))
				error_message("Unable to send signal .");
		}
		letter = 0;
		shifted = 0;
	}
	else
		shifted++;
	if (kill(info->si_pid, SIGUSR1))
		error_message("Unable to send signal .");
}

int	main(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof (struct sigaction));
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = print_message;
	if (sigaction(SIGUSR1, &action, NULL))
		error_message("Unable to set signal .");
	if (sigaction(SIGUSR2, &action, NULL))
		error_message("Unable to set signal .");
	ft_putstr_fd("PID[", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putendl_fd("]", 1);
	while (1)
		pause();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:19 by guiferre          #+#    #+#             */
/*   Updated: 2025/02/21 16:09:26 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

void	sig_handler(int sig, siginfo_t *info, void *c)
{
	static int		i;
	static pid_t	client_pid;

	i = 0;
	client_pid = 0;
	if (!client_pid)
		client_pid = info->si_pid;
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause ;
	return (0);
}
// server must print its pid (getpid)
// server must receive a string from a signal (SIGUSR1 and SIGUSR2) and print it

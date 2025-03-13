/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:19 by guiferre          #+#    #+#             */
/*   Updated: 2025/03/13 19:24:57 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static pid_t			client_pid;
	static int				i = 0;
	static unsigned char	c = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			ft_printf("%c", '\n');
			client_pid = 0;
			return ;
		}
		ft_printf("%c", c);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sa;

	ft_bzero(&s_sa, sizeof(s_sa));
	ft_printf("PID: ");
	ft_printf("%d", getpid());
	ft_printf("%c", '\n');
	s_sa.sa_sigaction = sig_handler;
	s_sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sa, 0);
	sigaction(SIGUSR2, &s_sa, 0);
	while (1)
		pause();
	return (0);
}

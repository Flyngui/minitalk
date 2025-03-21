/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:23 by guiferre          #+#    #+#             */
/*   Updated: 2025/03/21 02:54:26 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

static sig_atomic_t	g_waiting = 0;

static void	sig_handler(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
	{
		ft_printf("SIGUSR1");
		received++;
		g_waiting = 1;
	}
	else
	{
		ft_printf("%d", received);
		ft_printf("%c", '\n');
		exit(0);
	}
}

static void	sender(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		ft_printf("\nHello\n");
		g_waiting = 0;
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(50);
		}
		while (g_waiting == 0)
			usleep(1000);
		ft_printf("\nSent char\n");
	}
	i = 8;
	while (i--)
		kill(pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]) || ft_atoi(argv[1]) < 0)
		return (1);
	ft_printf("%s", "Sending: ");
	ft_printf("%d", ft_strlen(argv[2]));
	ft_printf("%c", '\n');
	ft_printf("%s", "Received: ");
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	sender(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}

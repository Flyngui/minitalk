/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:23 by guiferre          #+#    #+#             */
/*   Updated: 2025/03/12 20:59:39 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

static void	sig_handler(int sig)
{
	static int	back;

	back = 0;
	if (sig == SIGUSR1)
		back++;
	else
	{
		ft_printf("%d", back);
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
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
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

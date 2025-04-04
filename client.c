/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:23 by guiferre          #+#    #+#             */
/*   Updated: 2025/04/03 19:42:44 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int		g_waiting = 0;

static void	sig_handler(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
	{
		g_waiting = 0;
		received++;
	}
	else
	{
		ft_printf("Bits received: %d", received);
		ft_printf("%c", '\n');
		exit(0);
	}
}

static t_client	*get_args(int argc, char **argv)
{
	static t_client	args;
	int				pid;

	if (argc != 3)
		return (NULL);
	pid = ft_atoi(argv[1]);
	args.pid = pid;
	args.string = argv[2];
	return (&args);
}

static void	sender(t_client *client)
{
	int		i;

	while (*client->string++)
	{
		i = 8;
		while (i--)
		{
			if (*client->string >> i & 1)
				kill(client->pid, SIGUSR2);
			else
				kill(client->pid, SIGUSR1);
		}
		g_waiting = 1;
		while (g_waiting)
			;
		if (!client->string)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_client	*client;

	client = get_args(argc, argv);
	if (argc != 3 || !ft_strlen(argv[2]) || ft_atoi(argv[1]) < 0)
	{
		ft_printf("Usage: <server-pid> <string>\n");
		return (1);
	}
	ft_printf("%s", "Sending: ");
	ft_printf("%d", ft_strlen(argv[2]));
	ft_printf("%c", '\n');
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	sender(client);
	while (1)
		pause();
	return (0);
}

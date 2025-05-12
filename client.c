/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:23 by guiferre          #+#    #+#             */
/*   Updated: 2025/05/12 22:26:16 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_wait	*global_wait(void)
{
	static t_wait	wait;

	return (&wait);
}

t_client	*get_args(int argc, char **argv)
{
	static t_client	client_args;

	if (argc != 3)
		return (NULL);
	client_args.pid = ft_atoi(argv[1]);
	client_args.string = argv[2];
	return (&client_args);
}

void	sender(unsigned int c, int size, int pid)
{
	while (size--)
	{
		global_wait()->stop = 1;
		if ((c >> size) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(ft_printf("%s\n,INVALID PID"));
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(ft_printf("%s\n,INVALID PID"));
		}
		while (global_wait()->stop)
			;
	}
}

void	sig_handler(void)
{
	global_wait()->stop = 0;
}

int	main(int argc, char **argv)
{
	t_client	*client;

	if (argc != 3 || !ft_strlen(argv[2]) || ft_atoi(argv[1]) < 0)
	{
		ft_printf("Usage: <server-pid> <string>\n");
		return (1);
	}
	client = get_args(argc, argv);
	ft_printf("%s", "Sending: ");
	ft_printf("%d\n", ft_strlen(argv[2]));
	signal(SIGUSR1, (void *)sig_handler);
	while (*client->string)
		sender(*client->string++, 8, client->pid);
	sender('\0', 8, client->pid);
	return (0);
}

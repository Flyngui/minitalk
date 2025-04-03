/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:19 by guiferre          #+#    #+#             */
/*   Updated: 2025/04/03 19:15:36 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_strchrjoin(char *s1, char c)
{
	size_t	len1;
	size_t	i;
	char	*str;

	i = 0;
	len1 = ft_strlen(s1);
	str = malloc(len1 + 2);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	str[len1] = c;
	str[len1 + 1] = '\0';
	return (free(s1), str);
}

int	handle_signals(int sig, t_server *server)
{
	static int	i = 0;

	server->cur_bit |= (sig == SIGUSR2);
	if (++i < 8)
		server->cur_bit <<= 1;
	else
	{
		i = 0;
		if (!server->cur_char)
		{
			ft_printf("%s\n", server->string);
			free(server->string);
			server->string = NULL;
			return (2);
		}
		server->string = ft_strchrjoin(server->string, server->cur_char);
		if (!server->string)
			return (-1);
		server->cur_char = 0;
		return (1);
	}
	return (0);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static t_server	server;
	int				ret;

	(void)context;
	if (!server.pid)
		server.pid = info->si_pid;
	if (!server.string)
	{
		server.string = ft_strdup("");
		if (!server.string)
			return ;
	}
	ret = handle_signals(sig, &server);
	if (ret == 2)
	{
		kill(server.pid, SIGUSR2);
		server.pid = 0;
	}
	else
	{
		kill(server.pid, SIGUSR1);
	}
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

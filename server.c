/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:19 by guiferre          #+#    #+#             */
/*   Updated: 2025/05/12 22:00:45 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*str;
	size_t	len1;
	size_t	i;

	len1 = ft_strlen(s1);
	if ((int)ft_strlen(s1) == -1)
		len1 = 0;
	str = malloc(len1 + n + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len1)
		str[i] = s1[i];
	i = -1;
	while (++i < n)
		str[len1 + i] = s2[i];
	str[len1 + n] = '\0';
	return (free(s1), str);
}

void	signal_handler(int sig, t_server *server)
{
	server->cur_char <<= 1;
	if (sig == SIGUSR1)
		server->cur_char |= 1;
	server->cur_bit++;
	if (server->cur_bit >= 8)
	{
		if (!server->cur_char)
		{
			server->string = ft_strnjoin(server->string, "", 0);
			if (server->string)
			{
				ft_putstr_fd(server->string, 1);
				free(server->string);
				server->string = NULL;
			}
		}
		else
			server->string = ft_strnjoin(server->string,
					(char *)&server->cur_char, 1);
		server->cur_bit = 0;
		server->cur_char = 0;
	}
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static t_server	server;

	(void)context;
	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	if (!server.string)
	{
		server.string = ft_strdup("");
		if (!server.string)
			return ;
	}
	signal_handler(sig, &server);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_sa;

	ft_bzero(&s_sa, sizeof(s_sa));
	ft_printf("PID: ");
	ft_printf("%d", getpid());
	ft_printf("%c", '\n');
	s_sa.sa_sigaction = (void *)sig_handler;
	s_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sa.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGUSR1);
	sigaddset(&s_sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &s_sa, NULL);
	sigaction(SIGUSR2, &s_sa, NULL);
	while (1)
		pause();
}

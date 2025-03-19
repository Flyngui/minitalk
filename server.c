/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:13:19 by guiferre          #+#    #+#             */
/*   Updated: 2025/03/19 20:17:25 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

char	*ft_strchrjoin(char *s1, char c)
{
	size_t	len1;
	size_t	i;
	char	*str;

	i = 0;
	len1 = ft_strlen(s1);
	str = malloc(len1 + 2);
	if (!str)
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	str[len1] = c;
	str[len1 + 1] = '\0';
	return (free(s1), str);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static char				*string_save = NULL;
	static pid_t			client_pid;
	static int				i = 0;
	static unsigned char	c = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if (!string_save)
		string_save = ft_strdup("");
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			ft_printf("%s", string_save);
			ft_printf("%c", '\n');
			client_pid = 0;
			free(string_save);
			string_save = NULL;
			return ;
		}
		string_save = ft_strchrjoin(string_save, c);
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

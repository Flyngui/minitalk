/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guiferre <guiferre@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:09:14 by guiferre          #+#    #+#             */
/*   Updated: 2025/05/12 21:42:36 by guiferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>

# ifndef CHAR_BITS
#  define CHAR_BITS 8
# endif

typedef struct s_server
{
	int				pid;
	unsigned int	cur_char;
	int				cur_bit;
	char			*string;
}					t_server;

typedef struct s_wait
{
	int				stop;
}					t_wait;

typedef struct s_client
{
	int				pid;
	char			*string;
}					t_client;

#endif

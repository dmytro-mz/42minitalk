/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:56:23 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/21 10:49:51 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define SBYTE 8
# ifndef USLEEP_N
#  define USLEEP_N 100
# endif

# include "ft_printf.h"
# include <unistd.h>
# include <signal.h>

typedef struct s_client_state
{
    int is_ack_received;
    int is_send_next;
} t_client_state;

#endif
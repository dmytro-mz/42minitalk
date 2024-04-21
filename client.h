/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:56:23 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/21 14:01:58 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# ifndef USLEEP_N
#  define USLEEP_N 1000
# endif

# include "common.h"

typedef struct s_client_state
{
	int	is_ack_received;
	int	is_send_next;
}		t_client_state;

void	send_int(pid_t receiver, int n, int with_sleep);
void	send_data_with_sleep(pid_t receiver, char *data, size_t n_bytes);
void	send_data_with_sig(pid_t receiver, char *data, size_t n_bytes);

#endif
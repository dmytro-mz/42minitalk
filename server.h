/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:55:55 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/21 13:05:32 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "common.h"

typedef struct s_server_state
{
	int		total_byts;
	char	*str;
	pid_t	client_pid;
	int		client_pid_ready;
	size_t	i;
	char	*ptr;
	int		is_waiting;
}			t_server_state;

void		run_cycle(void);

#endif
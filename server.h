/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:55:55 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/19 22:24:07 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "ft_printf.h"
# include <unistd.h>
# include <signal.h>

typedef struct s_server_state
{
    int total_bits;
    char *str;
    int clinet_pid;
} t_server_state

#endif
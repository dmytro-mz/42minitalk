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

# define SBYTE 8

# include "ft_printf.h"
# include <unistd.h>
# include <signal.h>
# include <stddef.h>

typedef struct s_server_state
{
    int total_byts;
    char *str;
    pid_t client_pid;
    size_t i;
    char *ptr;
} t_server_state;

void run_cycle(void);

#endif
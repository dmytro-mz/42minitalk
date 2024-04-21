/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:55:58 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/21 13:06:51 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	set_sighandler(int to_set, void (*f)(int), int to_mask);
void	handle_sigusr1(int sig);
void	handle_sigusr2(int sig);
void	handle_sigusrx_common(int sig);

t_server_state	g_state;

int	main(void)
{
	set_sighandler(SIGUSR1, handle_sigusr1, SIGUSR2);
	set_sighandler(SIGUSR2, handle_sigusr2, SIGUSR1);
	ft_printf("PID: %d\n", getpid());
	while (1)
		run_cycle();
	return (0);
}

void	set_sighandler(int to_set, void (*handler)(int), int to_mask)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, to_mask);
	sigaction(to_set, &sa, NULL);
}

void	handle_sigusr1(int sig)
{
	handle_sigusrx_common(sig);
}

void	handle_sigusr2(int sig)
{
	handle_sigusrx_common(sig);
	*g_state.ptr |= 1;
}

void	handle_sigusrx_common(int sig)
{
	(void)sig;
	if (!(g_state.i % SBYTE) && g_state.i > 0)
		g_state.ptr++;
	*g_state.ptr = *g_state.ptr << 1;
	g_state.i++;
	g_state.is_waiting = 0;
}

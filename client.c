/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:56:19 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/21 13:06:03 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	set_sighandler(int to_set, void (*handler)(int));
void	handle_sigusr1(int sig);
void	handle_sigusr2(int sig);

t_client_state	g_state;

int	main(int ac, char *av[])
{
	pid_t	pid;

	g_state.is_ack_received = 0;
	if (ac != 3)
	{
		ft_putendl_fd("Invalid number of parameters", STDERR_FILENO);
		exit(1);
	}
	pid = ft_atoi(av[1]);
	if (!pid || kill(pid, 0) == -1)
	{
		ft_putendl_fd("Server PID invalid", STDERR_FILENO);
		exit(2);
	}
	set_sighandler(SIGUSR1, handle_sigusr1);
	set_sighandler(SIGUSR2, handle_sigusr2);
	g_state.is_send_next = 0;
	send_int(pid, getpid(), 1);
	send_int(pid, ft_strlen(av[2]), 0);
	send_data_with_sig(pid, av[2], ft_strlen(av[2]));
	ft_putendl_fd("Waiting for acknowledge...\n", STDOUT_FILENO);
	while (!g_state.is_ack_received)
	{
		usleep(10);
	}
}

void	set_sighandler(int to_set, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(to_set, &sa, NULL);
}

void	handle_sigusr1(int sig)
{
	g_state.is_send_next = 1;
}

void	handle_sigusr2(int sig)
{
	g_state.is_ack_received = 1;
	ft_putendl_fd("Server acknowledge received!", STDOUT_FILENO);
}

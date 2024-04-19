/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:55:58 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/19 22:24:08 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server_state state;

int	main(void)
{
	set_sighandler(SIGUSR1, handle_sigusr1, SIGUSR2);
	set_sighandler(SIGUSR2, handle_sigusr2, SIGUSR1);
	ft_printf("%d", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}

void	set_sighandler(int to_set, void (*f)(int), int to_mask)
{
	struct sigaction	sa;

	sa.sa_handler = f;
	sa.sa_flag = 0;
	sigemptyset(&sa.mask);
	sigaddset(&sa.mask, to_mask);
	sigaction(to_set, &sa, NULL);
}

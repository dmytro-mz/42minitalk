/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:26:46 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/21 12:58:33 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

extern t_client_state	g_state;

void	send_int(pid_t receiver, int n, int with_sleep)
{
	if (with_sleep)
		send_data_with_sleep(receiver, (char *)&n, sizeof(int));
	else
		send_data_with_sig(receiver, (char *)&n, sizeof(int));
}

void	send_data_with_sleep(pid_t receiver, char *data, size_t n_bytes)
{
	size_t	bytes_done;
	int		i;

	bytes_done = 0;
	while (bytes_done < n_bytes)
	{
		i = 0;
		while (i < SBYTE)
		{
			if ((*data >> (SBYTE - i - 1)) & 1)
				kill(receiver, SIGUSR2);
			else
				kill(receiver, SIGUSR1);
			i++;
			usleep(USLEEP_N);
		}
		data++;
		bytes_done++;
	}
}

void	send_data_with_sig(pid_t receiver, char *data, size_t n_bytes)
{
	size_t	bytes_done;
	int		i;

	bytes_done = 0;
	while (bytes_done < n_bytes)
	{
		i = 0;
		while (i < SBYTE)
		{
			while (!g_state.is_send_next)
				usleep(10);
			g_state.is_send_next = 0;
			if ((*data >> (SBYTE - i - 1)) & 1)
				kill(receiver, SIGUSR2);
			else
				kill(receiver, SIGUSR1);
			i++;
		}
		data++;
		bytes_done++;
	}
}

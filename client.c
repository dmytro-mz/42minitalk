/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:56:19 by dmoroz            #+#    #+#             */
/*   Updated: 2024/04/17 13:56:25 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void send_int(pid_t receiver, int n);
void send_data(pid_t receiver, char *data, size_t n_bytes);

int main(int ac, char *av[])
{
    pid_t pid;
    if (ac != 3)
    {
        ft_putendl_fd("Invalid number of parameters", STDOUT_FILENO);
        exit(1);
    }
    pid = ft_atoi(av[1]);
    if (!pid)
    {
        ft_putendl_fd("Server PID invalid", STDOUT_FILENO);
        exit(2);
    }
    ft_printf("PID: %d\n", getpid());
    ft_printf("Send PID...");
    send_int(pid, getpid());
    ft_printf("done!\n");
    ft_printf("Send str length...");
    send_int(pid, ft_strlen(av[2]));
    ft_printf("done!\n");
    ft_printf("Send str...");
    send_data(pid, av[2], ft_strlen(av[2]));
    ft_printf("done!\n");
}

void send_int(pid_t receiver, int n)
{
    ft_printf("(sending int: %d (of size %d))", n, sizeof(int));
    send_data(receiver, (char *)&n, sizeof(int));
}

void send_data(pid_t receiver, char *data, size_t n_bytes)
{
    size_t bytes_done;
    int i;

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

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

void send_int(pid_t receiver, int n, int with_sleep);
void send_data_with_sleep(pid_t receiver, char *data, size_t n_bytes);
void send_data_with_sig(pid_t receiver, char *data, size_t n_bytes);
void	set_sighandler(int to_set, void (*handler)(int));
void handle_sigusr1(int sig);
void handle_sigusr2(int sig);

t_client_state state;

int main(int ac, char *av[])
{
    pid_t pid;

    state.is_ack_received = 0;
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
    send_int(pid, getpid(), 1);
    send_int(pid, ft_strlen(av[2]), 0);
    send_data_with_sig(pid, av[2], ft_strlen(av[2]));
    while (!state.is_ack_received)
    {
        ft_putendl_fd("Waiting for acknowledge...\n", STDOUT_FILENO);
        pause();
    }
}

void send_int(pid_t receiver, int n, int with_sleep)
{
    if (with_sleep)
        send_data_with_sleep(receiver, (char *)&n, sizeof(int));
    else
        send_data_with_sig(receiver, (char *)&n, sizeof(int));

}

void send_data_with_sleep(pid_t receiver, char *data, size_t n_bytes)
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

void send_data_with_sig(pid_t receiver, char *data, size_t n_bytes)
{
    size_t bytes_done;
    int i;

    bytes_done = 0;
    while (bytes_done < n_bytes)
    {
        i = 0;
        while (i < SBYTE)
        {
            if (!state.is_send_next)
                pause();
            if ((*data >> (SBYTE - i - 1)) & 1)
                kill(receiver, SIGUSR2);
            else
                kill(receiver, SIGUSR1);
            state.is_send_next = 0;
            i++;
        }
        data++;
        bytes_done++;
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

void handle_sigusr1(int sig)
{
	state.is_send_next = 1;
}

void handle_sigusr2(int sig)
{
    state.is_ack_received = 1;
	ft_putendl_fd("Server acknowledge received!", STDOUT_FILENO);
}

#include "server.h"

void read_data(void *data, size_t size, int bytes_asc);
void inform_client(void);
void acknowledge(void);
void validate_client_pid(void);

extern t_server_state state;

void run_cycle(void)
{
    state.client_pid_ready = 0;
	state.client_pid = 0;
    ft_printf("  Reading client PID\n");
	read_data(&state.client_pid, sizeof(state.client_pid));
    validate_client_pid();
    ft_printf("  Client PID: %d\n", state.client_pid);
	state.total_byts = 0;
    ft_printf("  Reading string length\n");
	read_data(&state.total_byts, sizeof(state.total_byts));
    ft_printf("  String length: %d\n", state.total_byts);
	state.str = malloc(sizeof(char) * (state.total_byts + 1));
	state.str[state.total_byts] = 0;
    ft_printf("  Reading string...\n");
	read_data(state.str, state.total_byts);
	ft_putendl_fd(state.str, STDOUT_FILENO);
    free(state.str);
	acknowledge();
}

void read_data(void *data, size_t size)
{
	state.i = 0;
	state.ptr = data;
	while (state.i < SBYTE * size)
	{
        state.is_waiting = 1;
        while (state.is_waiting)
        {
            if (state.client_pid_ready)
                inform_client();
            usleep(10);
        }
        // if (state.client_pid_ready)
        //     inform_client();
        // if (state.is_waiting)
    	// 	pause();
	}
}

void inform_client(void)
{
	if (kill(state.client_pid, SIGUSR1) == -1)
    {
        ft_putendl_fd("Communication failed!", STDERR_FILENO);
        exit(1);
    }
}

void acknowledge(void)
{
	if (kill(state.client_pid, SIGUSR2) == -1)
        ft_putendl_fd("Acknowledge failed!", STDERR_FILENO);
}

void validate_client_pid(void)
{
    if (kill(state.client_pid, 0) == -1)
    {    
        ft_putendl_fd("Client PID invalid", STDERR_FILENO);
        exit(2);
    }
    state.client_pid_ready = 1;
}

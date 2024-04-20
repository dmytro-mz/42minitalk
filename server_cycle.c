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
	read_data(&state.client_pid, sizeof(state.client_pid), 1);
    validate_client_pid();
	state.total_byts = 0;
	read_data(&state.total_byts, sizeof(state.total_byts), 1);
	state.str = malloc(sizeof(char) * (state.total_byts + 1));
	state.str[state.total_byts] = 0;
	read_data(state.str, state.total_byts, 1);
	ft_putendl_fd(state.str, STDOUT_FILENO);
    free(state.str);
	acknowledge();
}

void read_data(void *data, size_t size, int bytes_asc)
{
	state.i = 0;
	state.ptr = data;
    if (!bytes_asc)
        state.ptr += size - 1;
	while (state.i < SBYTE * size)
	{
		if (!(state.i % 8) && state.i > 0)
			state.ptr += bytes_asc + (!bytes_asc) * -1;
        state.is_waiting = 1;
        if (state.client_pid_ready)
            inform_client();
        if (state.is_waiting)
    		pause();
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

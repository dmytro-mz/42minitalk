#include "server.h"

void read_data(void *data, size_t size, int bytes_asc);
void acknowledge(void);

extern t_server_state state;

void run_cycle(void)
{
	state.client_pid = 0;
	read_data(&state.client_pid, sizeof(state.client_pid), 1);
    ft_printf("Client PID: %d\n", state.client_pid);
	state.total_byts = 0;
	read_data(&state.total_byts, sizeof(state.total_byts), 1);
    ft_printf("Total bytes: %d\n", state.total_byts);
	state.str = malloc(sizeof(char) * (state.total_byts + 1));
	state.str[state.total_byts] = 0;
	read_data(state.str, state.total_byts, 1);
	ft_putendl_fd(state.str, STDOUT_FILENO);
    free(state.str);
	// acknowledge();
}

void read_data(void *data, size_t size, int bytes_asc)
{
	state.i = 0;
	state.ptr = data;
    if (!bytes_asc)
        state.ptr += size - 1;
	while (state.i < SBYTE * size)
	{
		if (!(state.i % 8) && state.i > 0){
            ft_printf("Byte: %d\n", *state.ptr);
			state.ptr += bytes_asc + (!bytes_asc) * -1;
        }
		pause();
	}
}

void acknowledge(void)
{
	kill(state.client_pid, SIGUSR1);
}

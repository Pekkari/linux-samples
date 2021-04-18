#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>

// We define our own max as otherwise
// size of local objects would overflow
#define FNAME_MAX 256
#define BUFFER_SIZE 1024

void sigint_handler () {
    int fd = 0;
    int pid = getpid();
    char schedstat_path[FNAME_MAX];
    sprintf(
        schedstat_path,
        "/proc/%d/schedstat",
        pid
    );
    char buffer[BUFFER_SIZE];

    printf("\n");
    if (fd = open(schedstat_path, O_RDONLY)) {
        long int cpu_time, waiting, timeslices, read_size;
        while(read_size = read(fd, buffer, BUFFER_SIZE))
            // Null terminate the buffer if it's shorter
            buffer[read_size] = '\0';
            sscanf(
                buffer,
                "%ld %ld %ld",
                &cpu_time,
                &waiting,
                &timeslices
            );
            printf("Sched values: %s", buffer);
            printf(
                "Average time computing: %f\n",
                cpu_time / (float) timeslices
            );
    }
    printf("Exiting process: %d\n", pid);
    exit(EXIT_SUCCESS);
}

int main(void) {
    long dumb = LONG_MIN;
    long counter = 0;

    signal(SIGINT, sigint_handler);

    while (1) {
        while (dumb < LONG_MAX) {
            dumb++;
        }
        counter++;
    }

    return 0;
}

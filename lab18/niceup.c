#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    int current_prio = 0;
    int pid = atoi(argv[1]);

    current_prio = getpriority(PRIO_PROCESS, pid);
    printf(
        "Nicing up process %d from %d -> %d\n",
        pid,
        current_prio++,
        current_prio
    );
    setpriority(PRIO_PROCESS, pid, current_prio);

    return 0;
}

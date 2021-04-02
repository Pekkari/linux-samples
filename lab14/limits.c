#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

void print_limits(struct rusage *limits) {
    printf(
        "User seconds: %ld\n"
        "System seconds: %ld\n"
        "Resident Set Size max: %ld\n"
        "Integral shared mem: %ld\n"
        "Integral unshared data size: %ld\n"
        "Integral unshared stack size: %ld\n"
        "Page reclaims: %ld\n"
        "Page faults: %ld\n"
        "Swaps: %ld\n"
        "Block input operations: %ld\n"
        "Block outputt operations: %ld\n"
        "Messages sent: %ld\n"
        "Messages received: %ld\n"
        "Signals received: %ld\n"
        "Voluntary context switches: %ld\n"
        "Involuntary context switches: %ld\n",
        limits->ru_utime.tv_sec,
        limits->ru_stime.tv_sec,
        limits->ru_maxrss,
        limits->ru_ixrss,
        limits->ru_idrss,
        limits->ru_isrss,
        limits->ru_minflt,
        limits->ru_majflt,
        limits->ru_nswap,
        limits->ru_inblock,
        limits->ru_oublock,
        limits->ru_msgsnd,
        limits->ru_msgrcv,
        limits->ru_nsignals,
        limits->ru_nvcsw,
        limits->ru_nivcsw
    );
}

void retrieve_and_print(int rusage_flag) {
    struct rusage *limits;
    if (!getrusage(rusage_flag, limits))
        print_limits(limits);
    else
        perror("Limit retrieval error: ");
}

int main(void)
{
    int status;
    struct rlimit orig_core_limit;
    struct rlimit new_core_limit;
    struct rlimit core_limit = {8 * 1024 * 1024, RLIM_INFINITY};

    fork();
    printf("\nPrinting self limits from all processes\n");
    retrieve_and_print(RUSAGE_SELF);

    printf("\nPrinting children limits, if any\n");
    retrieve_and_print(RUSAGE_CHILDREN);

    if (!getrlimit(RLIMIT_CORE, &orig_core_limit))
        printf(
            "\nPrinting original value of RLIMIT_CORE: %ld, %ld\n",
            orig_core_limit.rlim_cur,
            orig_core_limit.rlim_max
        );
    setrlimit(RLIMIT_CORE, &core_limit);
    if (!getrlimit(RLIMIT_CORE, &new_core_limit))
        printf(
            "\nPrinting new value of RLIMIT_CORE: %ld, %ld\n",
            new_core_limit.rlim_cur,
            new_core_limit.rlim_max
        );
    
    wait(&status);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_syscall_test 442

int main(void) {
    int i = 10;
    int j = 0;

    printf(
        "Syscall returned the answer to all questions: %ld",
        syscall(__NR_syscall_test, i)
    );

    return 0;
}

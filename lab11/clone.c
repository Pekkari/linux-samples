#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

#define CHILD_STACK_SIZE 256
int shared = 0;

int cloned_increase(void * args)
{
    printf("Updating shared value from child to: %d\n", ++shared);
    return 0;
}

int main(void)
{
    printf("This is the initial value of shared: %d\n", shared);

    void *childstack = malloc(CHILD_STACK_SIZE);
    clone(&cloned_increase, childstack + CHILD_STACK_SIZE, CLONE_VM, NULL);
    sleep(10);
    printf("Updating shared value from parent to: %d\n", ++shared);
    return 0;
}

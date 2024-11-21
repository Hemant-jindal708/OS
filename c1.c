#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <process.h>

int main(int argc, char *argv[])
{
    printf("PID of ex1.c = %d\n", getpid());
    char const *args[] = {"simple", NULL};
    execv("./c2", args);
    printf("Back to program1\n");
    return 0;
}

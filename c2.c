#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
printf("We are in program 2 \n");
printf("PID of program 2 is %d\n", getpid());
return 0;
}
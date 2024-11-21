#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Process
{
    int id;
    int burst;
    int TAT;
    int completetime;
    float Waiting;
    int arival;
};

void FCFS(Process process[], int num)
{
    sort(process, process + num, [](Process a, Process b)
         { return a.arival < b.arival; });
    process[0].TAT = process[0].burst;
    process[0].Waiting = 0;
    for (int i = 1; i < num; i++)
    {
        process[i].Waiting = process[i - 1].TAT - process[i].arival + process[i - 1].arival;
        process[i].TAT = process[i].Waiting + process[i].burst;
    }
    int sum = 0;
    for (int i = 1; i < num; i++)
    {
        sum += process[i].Waiting;
    }
    cout << "average waiting time =" << (float)sum / num;
}

int main()
{
    struct Process process[3];
    process[0].arival = 2;
    process[1].arival = 3;
    process[2].arival = 4;
    process[0].burst = 2;
    process[1].burst = 3;
    process[2].burst = 6;
    FCFS(process, 3);
}
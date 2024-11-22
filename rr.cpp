#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process
{
    int id;
    int arival;
    int burst;
    int TAT;
    int completion;
    int waiting;
    int remaing;
    bool completed = false;
    bool inReadyQueue = false;
};
void rr(vector<Process> process, int timeQuantam)
{
    for (int i = 0; i < process.size(); i++)
        process[i].remaing = process[i].burst;

    sort(process.begin(), process.end(), [](Process a, Process b)
         { return a.arival < b.arival; });
    int time = process[0].arival;
    int completed = 0;
    while (completed < process.size())
    {
        bool processfound=false;
        for (int i = 0; i < process.size(); i++)
        {
            if (process[i].arival <= time && process[i].remaing > 0)
            {
                int timecut=min(timeQuantam,process[i].remaing);
                process[i].remaing -= timecut;
                time+=timecut;
                if (process[i].remaing == 0)
                {
                    process[i].completion = time;
                    process[i].TAT = process[i].completion - process[i].arival;
                    process[i].waiting = process[i].TAT - process[i].burst;
                    completed++;
                }
                processfound=true;
            }
        }
        if(!processfound)
        {
            time++;
        }
    }
    int sum = 0;
    for (int i = 0; i < process.size(); i++)
    {
        sum += process[i].waiting;
    }
    cout << "average waiting time=" << (float)sum / process.size() << endl;
}
int main()
{
    vector<Process> Process;
    struct Process process[5];
    process[0].arival = 0;
    process[1].arival = 1;
    process[2].arival = 2;
    process[3].arival = 3;
    process[4].arival = 4;
    process[0].burst = 5;
    process[1].burst = 3;
    process[2].burst = 1;
    process[3].burst = 2;
    process[4].burst = 3;
    for (int i = 0; i < 5; i++)
    {
        Process.push_back(process[i]);
    }
    rr(Process, 2);
}
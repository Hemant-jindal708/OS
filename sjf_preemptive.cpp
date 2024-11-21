#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Process
{
    int id;
    int arival;
    int burst;
    int TAT;
    int completion;
    int waiting;
    int remaining;
};
void SJF(vector<Process> p)
{
    for (int i = 0; i < p.size(); i++)
        p[i].remaining = p[i].burst;
    sort(p.begin(), p.end(), [](Process a, Process b)
         { return a.arival < b.arival; });
    vector<Process> readyQueue;
    vector<Process> order;
    readyQueue.push_back(p[0]);
    int x = 1;
    int time = readyQueue[0].arival;
    int completed = 0;
    while (completed < p.size())
    {
        for (int i = x; i < p.size(); i++)
        {
            if (p[i].arival <= time)
            {
                readyQueue.push_back(p[i]);
                x++;
            }
        }
        if(readyQueue.empty())
        {
            time++;
            continue;
        }
        sort(readyQueue.begin(), readyQueue.end(), [](Process a, Process b)
             {
            if(a.burst==b.burst)
            {
                return a.arival<b.arival;
            }
            return a.burst<b.burst; });
        readyQueue.front().remaining--;
        time++;
        if(readyQueue.front().remaining==0)
        {
            readyQueue.front().completion=time;
            readyQueue.front().TAT=readyQueue.front().completion-readyQueue.front().arival;
            readyQueue.front().waiting=readyQueue.front().TAT-readyQueue.front().burst;
            order.push_back(readyQueue[0]);
            readyQueue.erase(readyQueue.begin());
            completed++;
        }
    }
    int sum=0;
    for (int i=0;i<p.size();i++)
    {
        sum+=order[i].waiting;
    }
    cout<<"Average Waiting time="<<(float)sum/p.size();
}
int main()
{
    vector<Process> Process;
    struct Process process[3];
    process[0].arival = 2;
    process[1].arival = 3;
    process[2].arival = 4;
    process[0].burst = 2;
    process[1].burst = 3;
    process[2].burst = 6;
    for (int i = 0; i < 3; i++)
    {
        Process.push_back(process[i]);
    }
    SJF(Process);
}
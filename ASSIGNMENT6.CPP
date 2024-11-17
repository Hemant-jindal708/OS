#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

struct Process
{
    int id, arrivalTime, burstTime, priority, waitingTime, turnAroundTime, remainingTime;
};

bool comparePriority(const Process &a, const Process &b)
{
    if (a.arrivalTime == b.arrivalTime)
        return a.priority < b.priority; 
    return a.arrivalTime < b.arrivalTime;
}
bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

float calculateAvgWaitTime(vector<Process> &processes)
{
    int totalWaitTime = 0;
    for (auto &p : processes)
    {
        totalWaitTime += p.waitingTime;
    }
    return (float)totalWaitTime / processes.size();
}

void prioritySchedulingNonPreemptive(vector<Process> &processes)
{
    sort(processes.begin(), processes.end(), comparePriority);

    int time = 0;
    for (auto &p : processes)
    {
        if (time < p.arrivalTime)
            time = p.arrivalTime;
        p.waitingTime = time - p.arrivalTime;
        time += p.burstTime;
        p.turnAroundTime = p.waitingTime + p.burstTime;
    }
}

void prioritySchedulingPreemptive(vector<Process> &processes)
{
    int n = processes.size(), completed = 0, currentTime = 0;
    vector<bool> isCompleted(n, false);

    while (completed != n)
    {
        int idx = -1;
        int highestPriority = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i])
            {
                if (processes[i].priority < highestPriority ||
                    (processes[i].priority == highestPriority && processes[i].arrivalTime < processes[idx].arrivalTime))
                {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            if (processes[idx].remainingTime == processes[idx].burstTime)
            {
                processes[idx].waitingTime = currentTime - processes[idx].arrivalTime;
            }
            currentTime++;
            processes[idx].remainingTime--;

            if (processes[idx].remainingTime == 0)
            {
                completed++;
                isCompleted[idx] = true;
                processes[idx].turnAroundTime = currentTime - processes[idx].arrivalTime;
            }
        }
        else
        {
            currentTime++;
        }
    }
}

void roundRobinScheduling(vector<Process> &processes, int quantum)
{
    queue<int> q;
    int n = processes.size();
    vector<bool> inQueue(n, false);
    int currentTime = 0, completed = 0;

    sort(processes.begin(), processes.end(), compareArrivalTime);

    q.push(0);
    inQueue[0] = true;

    while (completed != n)
    {
        int idx = q.front();
        q.pop();

        if (processes[idx].remainingTime == processes[idx].burstTime)
        {
            processes[idx].waitingTime = max(0, currentTime - processes[idx].arrivalTime);
        }

        int timeSlice = min(quantum, processes[idx].remainingTime);
        currentTime += timeSlice;
        processes[idx].remainingTime -= timeSlice;

        for (int i = 0; i < n; i++)
        {
            if (i != idx && !inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (processes[idx].remainingTime > 0)
        {
            q.push(idx);
        }
        else
        {
            processes[idx].turnAroundTime = currentTime - processes[idx].arrivalTime;
            completed++;
        }

        if (q.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (processes[i].remainingTime > 0)
                {
                    q.push(i);
                    break;
                }
            }
        }
    }
}

void displayResults(vector<Process> &processes)
{
    float avgWaitingTime = calculateAvgWaitTime(processes);
    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (auto &p : processes)
    {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t"
             << p.waitingTime << "\t\t" << p.turnAroundTime << "\n";
    }
    cout << "\nAverage Waiting Time: " << avgWaitingTime << " units\n";
}

int main()
{
    int n, choice, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time for preemptive
    }

    cout << "Select scheduling algorithm:\n";
    cout << "1. Priority Scheduling (Non-Preemptive)\n";
    cout << "2. Priority Scheduling (Preemptive)\n";
    cout << "3. Round Robin\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        prioritySchedulingNonPreemptive(processes);
        break;
    case 2:
        prioritySchedulingPreemptive(processes);
        break;
    case 3:
        cout << "Enter time quantum: ";
        cin >> quantum;
        roundRobinScheduling(processes, quantum);
        break;
    default:
        cout << "Invalid choice!";
        return 0;
    }

    displayResults(processes);

    return 0;
}

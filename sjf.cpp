#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Process {
    int id;
    int burst;
    int TAT;            // Turnaround Time
    int completetime;   // Completion Time
    float Waiting;      // Waiting Time
    int arival;         // Arrival Time
    bool completed = false; // Initially, process is not completed
    bool visited = false;   // Initially, process is not visited
};

void addprocess(vector<Process>& v, Process p[], int num, int time) {
    for (int i = 0; i < num; i++) {
        if (!p[i].visited && p[i].arival <= time) {
            p[i].visited = true;
            v.push_back(p[i]);
        }
    }
}

void SJF(Process process[], int num) {
    vector<Process> p; // Ready queue
    int completed = 0; // Number of completed processes
    int time = 0;      // Current time

    while (completed < num) {
        // Add processes that have arrived to the ready queue
        addprocess(p, process, num, time);

        // Sort the ready queue by burst time
        sort(p.begin(), p.end(), [](Process a, Process b) {
            return a.burst < b.burst;
        });

        if (p.empty()) {
            time++; // If no process is ready, increment time
        } else {
            // Pick the process with the shortest burst time
            Process& current = p.front();

            // Find and update the corresponding process in the main array
            for (int i = 0; i < num; i++) {
                if (process[i].id == current.id) {
                    process[i].completed = true;
                    process[i].completetime = time + process[i].burst;
                    process[i].TAT = process[i].completetime - process[i].arival;
                    process[i].Waiting = process[i].TAT - process[i].burst;

                    // Advance time by the burst time of the current process
                    time += process[i].burst;
                    completed++;
                    break;
                }
            }

            // Remove the completed process from the ready queue
            p.erase(p.begin());
        }
    }

    // Calculate average waiting time
    float totalWaitingTime = 0;
    for (int i = 0; i < num; i++) {
        totalWaitingTime += process[i].Waiting;
    }
    cout << "Average Waiting Time = " << totalWaitingTime / num << endl;
}

int main() {
    Process process[3];

    // Initialize processes
    process[0] = {0, 2, 0, 0, 0, 2, false, false};
    process[1] = {1, 3, 0, 0, 0, 3, false, false};
    process[2] = {2, 6, 0, 0, 0, 4, false, false};

    // Run SJF Scheduling
    SJF(process, 3);

    return 0;
}

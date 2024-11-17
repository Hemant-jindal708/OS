#include <iostream>
#include <queue>
using namespace std;

class Process
{
public:
    char id;
    int need[3];
    int allocated[3];
    bool exe = false;
};

bool canExecute(Process &process, int available[])
{

    if (process.need[0] > available[0] && process.need[1] > available[1] && process.need[2] > available[2])
    {
        return false;
    }
    return true;
}

void banker(Process process[], int number, int available[])
{
    queue<char> safeSequence;
    int executedCount = 0;

    while (executedCount < number)
    {
        bool allocated = false;

        for (int i = 0; i < number; i++)
        {
            if (!process[i].exe && canExecute(process[i], available))
            {
                for (int j = 0; j < 3; j++)
                {
                    available[j] += process[i].allocated[j];
                }

                process[i].exe = true;
                safeSequence.push(process[i].id);
                executedCount++;
                allocated = true;
            }
        }

        if (!allocated)
        {
            cout << "Safe sequence is not found" << endl;
            return;
        }
    }

    cout << "Safe sequence: ";
    while (!safeSequence.empty())
    {
        cout << safeSequence.front() << " -> ";
        safeSequence.pop();
    }
    cout << "done" << endl;
}

int main()
{
    Process process[3];

    int available[] = {1, 1, 1};

    process[0].id = '1';
    process[0].allocated[0] = 0;
    process[0].allocated[1] = 1;
    process[0].allocated[2] = 2;
    process[0].need[0] = 2;
    process[0].need[1] = 0;
    process[0].need[2] = 0;

    process[1].id = '2';
    process[1].allocated[0] = 0;
    process[1].allocated[1] = 1;
    process[1].allocated[2] = 1;
    process[1].need[0] = 1;
    process[1].need[1] = 0;
    process[1].need[2] = 0;

    process[2].id = '3';
    process[2].allocated[0] = 1;
    process[2].allocated[1] = 1;
    process[2].allocated[2] = 2;
    process[2].need[0] = 1;
    process[2].need[1] = 0;
    process[2].need[2] = 0;

    banker(process, 3, available);
}

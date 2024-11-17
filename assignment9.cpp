#include <iostream>
using namespace std;
class Block
{
public:
    int size;
    int allocatedTo;
    bool allocated;
    Block(int size)
    {
        this->size = size;

        allocatedTo = -1;
        allocated = false;
    }
};
class Process
{
public:
    int size;
    int blockAllocated;
    Process(int size)
    {
        this->size = size;
        blockAllocated = -1;
    }
};
void first_fit(Block blocks[], Process Processes[], int processNO, int BlockNo)
{
    for (int i = 0; i < processNO; i++)
    {
        for (int j = 0; j < BlockNo; j++)
        {
            if ((!blocks[j].allocated) && blocks[j].size >= Processes[i].size && Processes[i].blockAllocated == -1)
            {
                blocks[j].allocated = true;
                Processes[i].blockAllocated = j;
                blocks[j].allocatedTo = i;
                cout << Processes[i].size << " " << Processes[i].blockAllocated << " " << blocks[j].allocatedTo << " " << blocks[j].size << endl;
            }
        }
    }
    for (int i = 0; i < processNO; i++)
    {
        cout << "process id:" << i << " is allocated to: " << Processes[i].blockAllocated << endl;
    }
    cout << endl << endl;
}
void Best_fit(Block blocks[], Process Processes[], int processNO, int BlockNo)
{
    for (int i = 0; i < processNO; i++)
    {
        int index = -1;
        for (int j = 0; j < BlockNo; j++)
        {
            if ((!blocks[j].allocated) && blocks[j].size >= Processes[i].size)
            {
                if (index == -1 || blocks[index].size > blocks[j].size)
                {
                    index = j;
                }
            }
        }
        if (index != -1)
        {
            Processes[i].blockAllocated = index;
            blocks[index].allocated = true;
        }
    }
    for (int i = 0; i < processNO; i++)
    {
        cout << "process id:" << i << " is allocated to: " << Processes[i].blockAllocated << endl;
    }
}
void Worst_fit(Block blocks[], Process Processes[], int processNO, int BlockNo)
{
    for (int i = 0; i < processNO; i++)
    {
        int index = -1;
        for (int j = 0; j < BlockNo; j++)
        {
            if ((!blocks[j].allocated) && blocks[j].size >= Processes[i].size)
            {
                if (index == -1 || blocks[index].size < blocks[j].size)
                {
                    index = j;
                }
            }
        }
        if (index != -1)
        {
            Processes[i].blockAllocated = index;
            blocks[index].allocated = true;
        }
    }
    for (int i = 0; i < processNO; i++)
    {
        cout << "process id:" << i << " is allocated to: " << Processes[i].blockAllocated << endl;
    }
}
int main()
{
    Block blocks[] = {Block(100), Block(200), Block(400), Block(300)};
    Process Processes[] = {Process(200), Process(300), Process(100)};
    // first_fit(blocks, Processes, 3, 3);
    // Best_fit(blocks, Processes, 3, 4);
    // Worst_fit(blocks,Processes,3,4);
    
}
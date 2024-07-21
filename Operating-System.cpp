#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
using namespace std;
struct Process
{
    pid_t pid;
    string name;
    string state;
    int priority;
    int burstTime;
    int waitTime;
    int taTime;
    bool memoryallucation;
};
void CreateProcess(vector<Process> &p)
{
    system("clear");

    Process newproc;

    cout << "Enter the name for the process: ";
    cin >> newproc.name;
    cout << "Enter the Priority : ";
    cin >> newproc.priority;
    cout << "Enter the Burst time of process :";
    cin >> newproc.burstTime;

    newproc.state = "Ready";
    newproc.memoryallucation = false;
    newproc.pid = fork();

    if (newproc.pid == 0)
    {
        exit(0);
    }
    else if (newproc.pid > 0)
    {
        p.push_back(newproc);
    }
    else
    {

        cerr << "Error: Unable to create child process." << endl;
    }
    int a;
    cout << "Press 0 for back";
    cin >> a;
}
void DestoryProcess(vector<Process> &p)
{
    system("clear");

    if (p.empty())
    {
        cout << "No child Process created yet." << endl;
        sleep(2);
        return;
    }

    cout << "\nList of created Process:\n";
    cout << "PID\tName\n";
    for (const auto &process : p)
    {
        cout << process.pid << "\t" << process.name << endl;
    }

    int dp;
    cout << "Enter the id of Process you want to destory : ";
    cin >> dp;

    for (auto i = p.begin(); i != p.end(); ++i)
    {
        if (i->pid == dp)
        {
            cout << "Terminating process '" << i->name << "' wih PID: " << i->pid << endl;
            kill(i->pid, SIGTERM);
            waitpid(i->pid, NULL, 0);
            p.erase(i);
            return;
        }
    }

    cout << "Process ID" << dp << " not found." << endl;
}

void SuspendProcess(vector<Process> &p)
{
    system("clear");
    if (p.empty())
    {
        cout << "No child p to suspend." << endl;
        sleep(2);
        return;
    }

    cout << "\nList of created Process:\n";
    cout << "PID\tName\tState\n";
    for (const auto &process : p)
    {
        cout << process.pid << "\t" << process.name << "\t" << process.state << endl;
    }

    cout << "Enter the id of the process to suspend: ";
    int sid;
    cin >> sid;

    for (auto &process : p)
    {
        if (process.pid == sid)
        {
            cout << "Suspending process '" << process.name << "' with PID: " << process.pid << endl;
            process.state = "Suspend";
            kill(process.pid, SIGSTOP);
            sleep(2);
            return;
        }
    }
    cout << "Process '" << sid << "' not found." << endl;
    sleep(2);
}
void ResumeProcess(vector<Process> &p)
{
    system("clear");
    if (p.empty())
    {
        cout << "No child p to suspend." << endl;
        sleep(2);
        return;
    }

    cout << "\nList of created Process:\n";
    cout << "PID\tName\tState\n";
    for (const auto &process : p)
    {
        cout << process.pid << "\t" << process.name << "\t" << process.state << endl;
    }

    cout << "Enter the id of the process to Resume: ";
    int rid;
    cin >> rid;

    for (auto &process : p)
    {
        if (process.pid == rid && process.state == "Suspend")
        {
            cout << "Resume process '" << process.name << "' with PID: " << process.pid << endl;
            kill(process.pid, SIGCONT);
            process.state = "Ready";
            sleep(2);
            return;
        }
    }
    cout << "Process '" << rid << "' not found." << endl;
    sleep(2);
}
void BlockProcess(vector<Process> &p)
{
    system("clear");
    if (p.empty())
    {
        cout << "No child p to suspend." << endl;
        return;
    }

    cout << "\nList of created Process:\n";
    cout << "PID\tName\tState\n";
    for (const auto &process : p)
    {
        cout << process.pid << "\t" << process.name << "\t" << process.state << endl;
    }

    cout << "Enter the id of the process to Block: ";
    int bid;
    cin >> bid;

    for (auto &process : p)
    {
        if (process.pid == bid && process.state == "Ready")
        {
            cout << "Block process '" << process.name << "' with PID: " << process.pid << endl;
            process.state = "Block";
            kill(process.pid, SIGSTOP);
            sleep(2);
            return;
        }
    }

    cout << "Process '" << bid << "' not found." << endl;
    sleep(2);
}
void WakeupProcess(vector<Process> &p)
{
    system("clear");
    if (p.empty())
    {
        cout << "No child p to suspend." << endl;
        return;
    }

    cout << "\nList of created Process:\n";
    cout << "PID\tName\tState\n";
    for (const auto &process : p)
    {
        cout << process.pid << "\t" << process.name << "\t" << process.state << endl;
    }

    cout << "Enter the id of the process to Wake up: ";
    int sid;
    cin >> sid;

    for (auto &process : p)
    {
        if (process.pid == sid && process.state == "Block")
        {
            cout << "Wake up process '" << process.name << "' with PID: " << process.pid << endl;
            process.state = "Ready";
            kill(process.pid, SIGCONT);
            sleep(2);
            return;
        }
    }
    cout << "Process '" << sid << "' not found." << endl;
    sleep(2);
}
void FCFS(vector<Process> &p)
{
    system("clear");
    p[0].waitTime = 0;
    for (int i = 1; i < p.size(); i++)
    {
        p[i].waitTime = p[i - 1].waitTime + p[i - 1].burstTime;
    }
    for (int i = 0; i < p.size(); i++)
    {
        p[i].taTime = p[i].burstTime + p[i].waitTime;
    }

    cout << "Name\t\t\tBurstTime\t\tWaitTime\t\tTurnaroundTime\n";
    for (const auto &process : p)
    {
        cout << process.name << "\t\t\t" << process.burstTime << "\t\t\t" << process.waitTime
             << "\t\t\t" << process.taTime << endl;
    }
    int a;
    cout << endl
         << "Press 0 for back ";
    cin >> a;
}
void swap(Process &a, Process &b)
{
    Process temp = a;
    a = b;
    b = temp;
}
void sortProcessbyPriority(vector<Process> &p)
{

    for (int i = 0; i < p.size() - 1; ++i)
    {
        for (int j = 0; j < p.size() - i - 1; ++j)
        {
            if (p[j].priority < p[j + 1].priority)
            {
                swap(p[j], p[j + 1]);
            }
        }
    }
}
void PriorityS(vector<Process> &p)
{
    system("clear");
    sortProcessbyPriority(p);
    p[0].waitTime = 0;
    for (int i = 1; i < p.size(); i++)
    {
        p[i].waitTime = p[i - 1].waitTime + p[i - 1].burstTime;
    }
    for (int i = 0; i < p.size(); i++)
    {
        p[i].taTime = p[i].burstTime + p[i].waitTime;
    }

    cout << "Name\t\t\tPriority\t\tBurstTime\t\tWaitTime\t\tTurnaroundTime\n";
    for (const auto &process : p)
    {
        cout << process.name << "\t\t\t" << process.priority << "\t\t" << process.burstTime << "\t\t\t" << process.waitTime
             << "\t\t\t" << process.taTime << endl;
    }
    int a;
    cout << endl
         << "Press 0 for back ";
    cin >> a;
}
struct Page
{
    int id;
    int pagesize;
    int totalpages;
    int memorySize;
};

void Paging(vector<Process> &p, vector<Page> &pg)
{
    system("clear");
    Page page;
    if (p.empty())
    {
        cout << "There is no process for Paging" << endl;
        sleep(2);
        return;
    }

    while (true)
    {
        system("clear");
        cout << "1. Allocate Memory to Process\n";
        cout << "2. Display Memory Status\n";
        cout << "Press 0 for Back\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 0:
            exit(0);
        case 1:
            cout << "PID\tName" << endl;
            for (const auto &process : p)
            {
                cout << process.pid << "\t" << process.name << endl;
            }
            cout << "Enter the id of the process to Allucate Memory: ";
            int id;
            cin >> id;

            for (int i = 0; i < p.size(); ++i)
            {
                if (p[i].pid == id && p[i].memoryallucation == false)
                {
                    p[i].memoryallucation = true;
                    page.id = id;
                    cout << "Enter the memory of process (in KB): ";
                    cin >> page.memorySize;
                    ifstream configFile("pagesize.txt");
                    if (!configFile.is_open())
                    {
                        cerr << "Error: Unable to open configuration file." << endl;
                        
                    }
                    int pageSize;
                    configFile >> pageSize;
                    configFile.close();
                    page.pagesize = pageSize;
                    
                    page.totalpages = (page.memorySize + page.pagesize - 1) / page.pagesize;
                    pg.push_back(page);
                    cout << "Memory Allucated to this Process " << endl;
                    sleep(1);
                    return;
                }
            }

            cout << "Process '" << id << "' not found. Or This Process has alreay memory allucated" << endl;
            break;

        case 2:
            cout << "PID\tPMemorysize\tPage Size\t Total Pages\t" << endl;
            for (const auto &paging : pg)
            {
                cout << paging.id << "\t" << paging.memorySize << "\t\t" << paging.pagesize << "\t\t" << paging.totalpages << endl;
            }

            int a;
            cout << "Press 0 for back ";
            cin >> a;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}
const int MAX_SIZE = 1000;

int findPageInFrame(int frame[], int size, int page)
{
    for (int i = 0; i < size; ++i)
    {
        if (frame[i] == page)
        {
            return i;
        }
    }
    return -1;
}

int lruPageReplacement(int totalFrames, int referenceString[], int totalPages)
{
    int frame[MAX_SIZE];
    int pageFaults = 0;
    int pageHits = 0;

    for (int i = 0; i < totalPages; ++i)
    {
        int page = referenceString[i];

        int pageIndex = findPageInFrame(frame, totalFrames, page);

        if (pageIndex == -1)
        {
            if (totalFrames > 0)
            {
                frame[totalFrames - 1] = page;
                --totalFrames;
            }
            else
            {
                for (int j = 0; j < totalFrames - 1; ++j)
                {
                    frame[j] = frame[j + 1];
                }
                frame[totalFrames - 1] = page;
            }

            ++pageFaults;
        }
        else
        {
            for (int j = pageIndex; j < totalFrames - 1; ++j)
            {
                frame[j] = frame[j + 1];
            }
            frame[totalFrames - 1] = page;

            ++pageHits;
        }
    }

    cout << "Total Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits: " << pageHits << endl;

    return pageFaults;
}

void LRU()
{
    int totalFrames, totalPages;

    cout << "Enter the total number of frames: ";
    cin >> totalFrames;

    cout << "Enter the total number of pages: ";
    cin >> totalPages;

    int referenceString[MAX_SIZE];

    cout << "Enter the reference string (space-separated): ";
    for (int i = 0; i < totalPages; ++i)
    {
        cin >> referenceString[i];
    }

    int pageFaults = lruPageReplacement(totalFrames, referenceString, totalPages);

    int a;
    cout << "Enter 0 for back ";
    cin >> a;
}

void ProcessManagment(vector<Process> &process)
{
    system("clear");
    while (true)
    {
        system("clear");
        cout << "1. Create Process" << endl;
        cout << "2. Destroy Process " << endl;
        cout << "3. Suspend Process" << endl;
        cout << "4. Resume Process" << endl;
        cout << "5. Block Process" << endl;
        cout << "6. Wakeup Process" << endl;
        cout << "Press 0 For Back" << endl
             << endl;

        int choice;
        cout << "Enter Your Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            CreateProcess(process);
            break;
        case 2:
            DestoryProcess(process);
            break;
        case 3:
            SuspendProcess(process);
            break;
        case 4:
            ResumeProcess(process);
            break;
        case 5:
            BlockProcess(process);
            break;
        case 6:
            WakeupProcess(process);
            break;
        default:
            return;
            break;
        }
    }
}
void Scheduling(vector<Process> &process)
{
    system("clear");
    while (true)
    {
        cout << endl;
        system("clear");
        cout << "1. FCFS" << endl;
        cout << "2. Priority " << endl;
        cout << "Press 0 For Back" << endl
             << endl;

        int choice;
        cout << "Enter Your Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            FCFS(process);
            break;
        case 2:
            PriorityS(process);
            break;
        default:
            return;
            break;
        }
    }
}
void MemoryManagement(vector<Process> &process, vector<Page> &pages)
{
    while (true)
    {
        system("clear");
        cout << endl;
        cout << "1. Paging" << endl;
        cout << "2. Replacement Algorithm (LRU) " << endl;
        cout << "Press 0 For Back" << endl
             << endl;

        int choice;
        cout << "Enter Your Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Paging(process, pages);
            break;
        case 2:
            LRU();
            break;
        default:
            return;
            break;
        }
    }
}
void ShowPCB(const vector<Process> &p)
{
    system("clear");
    if (p.empty())
    {
        cout << "No Process Create Yet" << endl;
        sleep(2);
        return;
    }

    cout << "\nList of created Process:\n";
    cout << "PID\t\tName\t\tState\t\tPriority\n";
    for (const auto &process : p)
    {
        cout << process.pid << "\t\t" << process.name << "\t\t" << process.state << "\t\t" << process.priority << endl;
    }
    cout << endl
         << "Press 0 for back ";
    int c;
    cin >> c;
}
void OperatingSystem()
{
    system("clear");
    vector<Process> process;
    vector<Page> pages;
    while (true)
    {
        system("clear");
        cout << "1. Process Management" << endl;
        cout << "2. Process Scheduling " << endl;
        cout << "3. Memory Management" << endl;
        cout << "4. PCB " << endl;
        cout << "0. Exit" << endl;

        int choice;

        cout << "Enter Your Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            ProcessManagment(process);
            break;
        case 2:
            Scheduling(process);
            break;
        case 3:
            MemoryManagement(process, pages);
            break;
        case 4:
            ShowPCB(process);
            break;
        case 5:

            break;
        default:
            exit(0);
            break;
        }
    }
}

int main()
{
    OperatingSystem();
    return 0;
}
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// Function prototypes
void roundRobinScheduling();
void shortestJobFirstScheduling();

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];
    int t = 0; // Current time
    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true)
            break;
    }
}

// Function to calculate turnaround time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average time for Round Robin
void findavgTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);
    cout << "Processes " << " Burst time " << " Waiting time " << " Turn around time\n";
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i + 1 << "\t\t" << bt[i] << "\t " << wt[i] << "\t\t " << tat[i] << endl;
    }
    cout << "Average waiting time = " << (float)total_wt / (float)n << endl;
    cout << "Average turn around time = " << (float)total_tat / (float)n << endl;
}

// Round Robin Scheduling function
void roundRobinScheduling() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {10, 5, 8};
    int quantum;
    cout << "Enter time quantum for Round Robin: ";
    cin >> quantum;
    findavgTime(processes, n, burst_time, quantum);
}

// Structure for Shortest Job First (SJF) scheduling
typedef struct proccess {
    int at, bt, ct, ta, wt, btt;
    string pro_id;
} Schedule;

bool compare(Schedule a, Schedule b) {
    return a.at < b.at;
}

bool compare2(Schedule a, Schedule b) {
    return a.bt < b.bt;
}

// Shortest Job First Scheduling function
void shortestJobFirstScheduling() {
    Schedule pro[10];
    int n, i, j, pcom;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter Process ID, Arrival Time, Burst Time:\n";
    for (i = 0; i < n; i++) {
        cin >> pro[i].pro_id;
        cin >> pro[i].at;
        cin >> pro[i].bt;
        pro[i].btt = pro[i].bt;
    }
    sort(pro, pro + n, compare);
    i = 0;
    pcom = 0;
    while (pcom < n) {
        for (j = 0; j < n; j++) {
            if (pro[j].at > i)
                break;
        }
        sort(pro, pro + j, compare2);
        if (j > 0) {
            for (j = 0; j < n; j++) {
                if (pro[j].bt != 0)
                    break;
            }
            if (pro[j].at > i) {
                i = pro[j].at;
            }
            pro[j].ct = i + 1;
            pro[j].bt--;
        }
        i++;
        pcom = 0;
        for (j = 0; j < n; j++) {
            if (pro[j].bt == 0)
                pcom++;
        }
    }
    cout << "ProID\tAtime\tBtime\tCtime\tTtime\tWtime\n";
    for (i = 0; i < n; i++) {
        pro[i].ta = pro[i].ct - pro[i].at;
        pro[i].wt = pro[i].ta - pro[i].btt;
        cout << pro[i].pro_id << "\t" << pro[i].at << "\t" << pro[i].btt << "\t" << pro[i].ct << "\t" << pro[i].ta << "\t" << pro[i].wt << endl;
    }
}

// Main function to drive the menu
int main() {
    int choice;
    do {
        cout << "Menu:\n";
        cout << "1. Round Robin Scheduling\n";
        cout << "2. Shortest Job First Scheduling\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                roundRobinScheduling();
                break;
            case 2:
                shortestJobFirstScheduling();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    } while (choice != 3);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>

using namespace std;

int n;

struct process
{
    int ID, AT, BT, CT,  WT, TAT, interruptted, completeOnQueue;
} Q0[10], Q1[10], Q2[10], D[10];

void sortByArrival()
{
    struct process temp;
    int i, j;
    for (i = 0; i < n; ++i)
    {
        for (j = i = 1; j < n; ++j)
        {
            if (Q0[j].AT > Q0[i].AT)
            {
                temp = Q0[i];
                Q0[i] = Q0[j];
                Q0[j] = temp;
            }            
        }
    }
}


int main()
{
    int i, ID;
    int tq1 = 8, tq2 = 16;

    cout << "Enter no of process: ";
    cin >> n;

    for (i = 0, ID = 1; i < n; ++i, ++ID)
    {
        Q0[i].ID = ID;
        cout << "Enter arrival time for P" << Q0[i].ID << ": ";
        cin >> Q0[i].AT;
        cout << "Enter burst time for P" << Q0[i].ID << ": ";
        cin >> Q0[i].BT;
    }
    sortByArrival();

    int completeTime = 0;
    int processTime;

    // process in Q0 with tq = 8
    for (i = 0; i < n; ++i)
    {
        Q1[i] = Q0[i];

        if (Q0[i].BT > tq1)
        {
            Q1[i].BT -= tq1;
            completeTime += tq1;
            processTime = tq1;
        } else 
        {
            Q1[i].BT = 0;
            D[i] = Q0[i];
            D[i].completeOnQueue = 0;
            D[i].interruptted = 0;
            D[i].TAT = completeTime - Q0[i].AT;
            processTime = Q0[i].BT;
        }
        cout << "P" << Q0[i].ID << " at Queue 0 it is executed for " << processTime << endl;
    }

    // process in Q1 with tq = 16
    for (i = 0; i < n; ++i)
    {
        Q2[i] = Q1[i]; // move to queue 2

        if (Q1[i].BT > tq2)
        {
            Q2[i].BT -= tq2;
            completeTime += tq2;
            processTime = tq2;
        } else 
        {
            Q1[i].BT = 0;
            D[i] = Q1[i];
            D[i].completeOnQueue = 1;
            D[i].interruptted = 1;
            D[i].TAT = completeTime - D[i].AT;
            processTime = Q1[i].BT;
        }
        cout << "P" << Q1[i].ID << " at Queue 1 it is executed for " << processTime << endl;
    }

        // process in Q2 with FCFS
    for (i = 0; i < n; ++i)
    {
        if (Q2[i].BT > 0)
        {
            D[i].completeOnQueue = 2;
            D[i].interruptted = 2;
            D[i].TAT = completeTime - D[i].AT;
            processTime = Q2[i].BT;
        }
        cout << "P" << Q2[i].ID << " at Queue 2 it is executed for " << processTime << endl;
    }

    // summary
    for (i = 0; i < n; ++i)
    {
        cout << "P" << D[i].ID << " is interrupted " << D[i].interruptted << " times, completes on queue #" << D[i].completeOnQueue << ", and TAT for P" << D[i].ID << " is  " << D[i].TAT << endl;
    }

    return 0;
}

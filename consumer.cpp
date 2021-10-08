#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <queue>
#include <sys/mman.h>
#include <iostream>

struct process{
std::string id{""};
std::string at{""};
std::string bt{""};
int qnum{0};
int exit_time{1};
int num_of_interrupts{0};
};

// Fills the process array with the data from producer.cpp
void fillProcessArray(std::string ptrString, process processArray[], int processArraySize, int i)
{
    int j;

    for(j=0; j < processArraySize; j++)
    {
        while(isdigit(ptrString[i]) || isalpha(ptrString[i]))
        {
            processArray[j].id += ptrString[i];
            i++;
        }
        i++;
        while(isdigit(ptrString[i]) || isalpha(ptrString[i]))
        {
            processArray[j].at += ptrString[i];
            i++;
        }
        i++;
        while(isdigit(ptrString[i]) || isalpha(ptrString[i]))
        {
            processArray[j].bt += ptrString[i];
            i++;
        }
        i++;
    }
}

int main()
{
// intilaizing shared memory space

/* the size (in bytes) of shared memory object */
const int SIZE = 4096;
/* name of the shared memory object */
const char *name = "Shared Memory";
/* shared memory file descriptor */
int fd;
/* pointer to shared memory obect */
char *ptr;
/* open the shared memory object */
fd = shm_open(name, O_RDWR, 0666);
/* memory map the shared memory object */
ptr = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
/* read from the shared memory object */

std::vector<process> process_vec;

std::cout << "passed c string: ";
printf("%s",(char *)ptr);
std::cout << std::endl;

std::string ptrString = std::string(ptr); // A variable that will hold the contents of "ptr" in a string format

std::string stringProcessArraySize; // The size of the array in a string format
int processArraySize; // The size of the array

int i = 0;

// Retrieves the number of processes and stores it in a string format
while(isdigit(ptrString[i]))
{
    stringProcessArraySize += ptrString[i];
    i++;
}
i++;

// Converts the number of processes from a string to an int
processArraySize = std::stoi(stringProcessArraySize);

// Check to see if the number of processes is correct
std::cout << "Number of processes: " << processArraySize << std::endl;

process processArray[processArraySize]; // Creates an array of processes with the number of processes as its size

// Parses the data from ptrString to a process array
fillProcessArray(ptrString, processArray, processArraySize, i);

// Check to see if the contents of the array are correct by printing the data
std::cout << "Processes Data: " << std::endl;
for(i=0; i< processArraySize; i++)
{
    std::cout << "Process Id: " << processArray[i].id << " ";
    std::cout << "Arrival Time: " << processArray[i].at << " ";
    std::cout << "Burst Time: " << processArray[i].bt;
    std::cout << std::endl;
}

return 0;
}

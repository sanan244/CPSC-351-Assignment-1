#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include <vector>

struct process{
int ID;
int AT;
int BT;
int interupt_cnt;
int TAT;
}Q0[10], Q1[10], Q2[10];// Three Queues

int main(int argc, char *argv[]){

int i = 1;
int j = 0;
int arraySize = (argc-1)/3; // Divide number of command line arguments by 3
process processArray[arraySize]; // Set this number to the size of the array

// Assign ID, AT, and BT to each processArray element
while(j < arraySize)
{
    processArray[j].ID = atoi(argv[i]);
    i++;
    processArray[j].AT = atoi(argv[i]);
    i++;
    processArray[j].BT = atoi(argv[i]);
    i++;
    j++;
}

// Check for correct data by printing the elements of the array
for(int i=0; i < arraySize; i++)
{
    std::cout << processArray[i].ID << " ";
    std::cout << processArray[i].AT << " ";
    std::cout << processArray[i].BT << " ";
}

const int SIZE = 4096;

const char *name = "OS";

const char *message_0 = "Hello";
const char *message_1 = "World";

int shm_fd;

void *ptr;

shm_fd = shm_open(name,O_CREAT | O_RDWR, 0666);

ftruncate(shm_fd, SIZE);

ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

sprintf((char*)ptr, "%s", message_0);
ptr += strlen(message_0);

sprintf((char*)ptr, "%s", message_1);
ptr += strlen(message_1);

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

struct process{
int ID;
int AT;
int BT;
int interupt_cnt;
int TAT;
}Q0[10], Q1[10], Q2[10];// Three Queues

int main(int id1[], int at1[], int bt1[], int id2[], int at2[], int bt2){

// configure share memory 
const int SIZE = 4096;
const char *name = "OS";

// create variables for command line input
int *id1_ = id1;
int *id2_ = id2;

int *at1_ = at1;
int *at2_ = at2;

int *bt1_ = bt1;
int *bt2_ = bt2;


int shm_fd;
void *ptr;

shm_fd = shm_open(name,O_CREAT | O_RDWR, 0666);

ftruncate(shm_fd, SIZE);

ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

// write to the shared memory object
sprintf((char*)ptr, "%s", message_0);
*ptr += strlen(message_0);

sprintf((char *)ptr, "%s", message_1);
*ptr += strlen(message_1);

sprintf((char*)ptr, "%s", id1_);
sprintf((char *)ptr, "%s", id2_);
sprintf((char *)ptr, "%s", at1_);
sprintf((char *)ptr, "%s", at2_);
sprintf((char *)ptr, "%s", bt1_);
sprintf((char *)ptr, "%s", bt2_);

}
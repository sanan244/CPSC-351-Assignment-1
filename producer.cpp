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

int main(){

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

sprintf((char *)ptr, "%s", message_1);
ptr += strlen(message_1);

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>

using namespace std;
 /*
struct process{
char ID;
char AT;
char BT;
char charerupt_cnt;
char TAT;
}Q0[10], Q1[10], Q2[10];// Three Queues
*/

int main(){
// configure share memory
const int SIZE = 4096;
const char *name = "OS";
char shm_fd;
void *ptr;

// set input variables
 char id1_[2];
 char id2_[2];

 char at1_[2];
 char at2_[2];

 char bt1_[2];
 char bt2_[2];

// create command line input
printf("Enter P1 ID: ");
cin >> id1_;
cin.clear();
printf("Enter P1 AT: ");
cin >> at1_;
cin.clear();
printf("Enter P1 BT: ");
cin >> bt1_;
cin.clear();
printf("Enter P2 ID: ");
cin >> id2_;
cin.clear();
printf("Enter P2 AT: ");
cin >> at2_;
cin.clear();
printf("Enter P2 BT: ");
cin >> bt2_;
cin.clear();

printf("...Input ready.\n");

shm_fd = shm_open(name,O_CREAT | O_RDWR, 0666);
printf("...shm opened.\n");

ftruncate(shm_fd, SIZE);
printf("...ftruncated.\n");

ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
printf("...ptr mapped.\n");

// write to the shared memory object
sprintf((char *)ptr, "%s", id1_);
ptr += strlen(id1_);
sprintf((char *)ptr, "%s", at1_);
ptr += strlen(at1_);
sprintf((char *)ptr, "%s", bt1_);
ptr += strlen(bt1_);

sprintf((char *)ptr, "%s", id2_);
ptr += strlen(id2_);
sprintf((char *)ptr, "%s", at2_);
ptr += strlen(at2_);
sprintf((char *)ptr, "%s", bt2_);
ptr += strlen(bt2_);


printf("...Data written to memory.\n");
printf("Producer complete.\n");
return 0;
}
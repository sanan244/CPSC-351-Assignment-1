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

using namespace std;


int main(){
// configure share memory
const int SIZE = 4096;
const char *name = "OS";
char shm_fd;
void *ptr;

// set input variables
int num;
 char id1_[3];
 char at1_[3];
 char bt1_[3];

 //ask for process count
 printf("How many processes would you like to add?:");
 cin >> num;
 char *previous_ptr;
 // Loop will create a vector of processes
 for(int i = 1; i < num + 1; i++){

   cout << "Enter ID for process " << i << ":";
   cin >> id1_;
   cin.clear();
   cout << "Enter AT for process " << i << ":";
   cin >> at1_;
   cin.clear();
   cout << "Enter BT for process " << i <<":";
   cin >> bt1_;
   cin.clear();
/*
   // add input to struct then add struct to back of vector
   cur_process.ID = id1_;
   cur_process.AT = at1_;
   cur_process.BT = bt1_;
   process_.push_back(cur_process);
*/
//printf("...Input ready.\n");

shm_fd = shm_open(name,O_CREAT | O_RDWR, 0666);
//printf("...shm opened.\n");
ftruncate(shm_fd, SIZE);
//printf("...ftruncated.\n");
ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
printf("...ptr mapped.\n");

// write to the shared memory object
//ptr += sprintf((char *)ptr, "%s ", previous_ptr);
//ptr += strlen(id1_);
ptr += sprintf((char *)ptr, "%s ", id1_);
//ptr += strlen(id1_);
ptr += sprintf((char *)ptr, "%s ", at1_);
//ptr += strlen(at1_);
ptr += sprintf((char *)ptr, "%s", bt1_);
//ptr += strlen(bt1_);
//previous_ptr = id1_ + at1_ + bt1_;
//cout << "...Previous ptr:" << previous_ptr << "\n";
printf("...Process written to memory.\n");
}

printf("Producer complete.\n");
return 0;
}

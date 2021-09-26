#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

struct process{
int ID;
int AT;
int BT;
int interupt_cnt;
int TAT;
}Q0[10], Q1[10], Q2[10];// Three Queues

// Function to determine if interrupt or not
bool interrupt_(struct process input){
  bool bool_ = false;
  //code here

  //increment interuppt count of process if true
  input.interupt_cnt += 1;

  return bool_;
}

//Function to calculate TAT
int  calc_tat(){
    int tat = 0;

  return tat;
}

// Timer function



int main(int id1[], int at1[], int bt1[], int id2[], int at2[], int bt2[]){
//Assign input values to struct input1
struct process input1;
input1.ID = *id1;
input1.AT = *at1;
input1.BT = *bt1;
// Assign input values to struct input 2
struct process input2;
input2.ID = *id2;
input2.AT = *at2;
input2.BT = *bt2;

// Initialize shared memory variables
  const int SIZE = 4096;
  /* name of the shared memory object */
  const char* name = "Memory";

// more code


// output

return 0;
}
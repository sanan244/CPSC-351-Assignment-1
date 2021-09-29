#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

//Global struct and vector
// Struct for each process
struct process{
char* ID;
char* AT;
char* BT;
char charerupt_cnt;
char TAT;
}Q0[10], Q1[10], Q2[10];// Three Queues
// Vector of all dynamically created processes
std::vector<char *>ptr_input;

// add input variables into digits list
void split(std::list<int>&digits, int x){
  if (0 == x) {
      digits.push_back(0);
    }
  else {
      while (x != 0) {
        int last = x % 10;
        digits.push_front(last);
        x = (x - last) / 10;
      }
    }
}

int main(){

//Initialize variables
const int SIZE = 4096;
const char *name = "OS";
int shm_fd;
void *ptr;
bool exit = false;

// loop will continue to read shared memory until the ptr value is 'done'
// when ptr = 'done' exit = TRUE
//while(exit == false){
    // read shared memory
    shm_fd = shm_open(name,O_RDONLY, 0666);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    //only add new ptr if it does not exist
  //  if(find(ptr_input.begin(), ptr_input.end(),(char *)ptr)  == ptr_input.end()){
        printf("%s", (char *)ptr);
        std::cout << "\n";
        ptr_input.push_back((char *)ptr);

        // turn string input into int
        int x;
        //sscanf((char *)ptr, "%d", &x);
        //printf("\nThe value of int x is: %d\n", x);

        //split int variable into digits and add all digits to the list 'digits' above
        //split(digits,x);
        shm_unlink(name);
  //}


//}//end of exit Loop

/*
//Travers digits list and execute scheduling algorithm according to each variable
for (it = digits.begin(); it != digits.end(); ++it){
  if(it == 0){
    id1 = digits[it];
    printf(id);}
  else if(it == 1){}
  else if(it == 2){}
  else if(it == 3){}
  else if(it == 4){}
  else{bt2 = digits[it]}
}
*/
return 0;
}

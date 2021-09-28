#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <list>

//global variables
std::list<int>digits;
std::list<int>::iterator it;

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

const int SIZE = 4096;

const char *name = "OS";

int shm_fd;

void *ptr;

shm_fd = shm_open(name,O_RDONLY, 0666);

ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

//printf("%s", (char *)ptr);
// Prepare (char*)ptr data for scheduling

// turn string input into int
int x;
sscanf((char *)ptr, "%d", &x);
printf("\nThe value of int x : %d", x);

//split int variable into digits and add all digits to the list 'digits' above
split(digits,x);
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

shm_unlink(name);
return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <queue>
#include <queue>
#include <sys/mman.h>
#include <iostream>
#include <string>



// determine if process finishes within time limit
// q should be 0 or 1 so the function can use 8 or 16 secs
int calculate_runtime(int bt, int q){
  int tq0{8};
  int tq1{16};
  int interrupt = 0;// 0 = no interrupt, 1 = yes interrupt
  if(q == 0){
// time 8 secs
  for(int i = 0; i < tq0; i++){
    if(bt > i){
      bt = bt -1;
      i = i + 1;
      }
    }
    if(bt != 0){interrupt = 1;}
  }

  // time 16 secs
  else if(q == 1){
    for(int i = 0; i < tq1; i++){
      if(bt > i){
        bt = bt -1;
        i = i + 1;
        }
      }
      if(bt != 0){interrupt = 1;}
    }
  return bt, interrupt;
}

int main()
{

struct process{
std::string id{""};
int at{0};
int bt{0};
int qnum{0};
int exit_time{1};
int num_of_interrupts{0};
};
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
const char* delim{","};
char* token = strtok(ptr,delim);
std::cout <<"our first process has a pid of: " << token <<std::endl;

while(token != NULL)
{
  process temp_process;

  std::cout << token << std::endl;
  temp_process.id = token;

  token = strtok(NULL,delim);


std::cout  << token <<std::endl;
temp_process.at = atoi(token);

token = strtok(NULL,delim);

std::cout << token <<std::endl;
temp_process.bt = atoi(token);
process_vec.push_back(temp_process);

token = strtok(NULL,delim);

}

std:: cout << "test"<< std::endl;

std:: cout << "my consumer recieved " << process_vec.size() << " process." <<std::endl;

std::queue<process> q0,q1,q2;
// queue 2
int i = 0;
std:: cout << "...Process:0" << "entered Q0." << std:: endl;
q0.push(process_vec[0]);
std:: cout << "...Process:1" << "entered Q1." << std:: endl;
q0.push(process_vec[1]);
while (i < process_vec.size())
{
  // run Queue 0 and process 0
  if(i == 0){
    int interrupt;
    process_vec[i].bt,interrupt = calculate_runtime(process_vec[i].bt, i = 0);
    //update interupt
    if(interrupt == 1){process_vec[i].num_of_interrupts += 1;}
    //update exit time
    //send to next queue if not complete
    if(process_vec[i].bt != 0){
      q1.push(process_vec[i]);
      q0.pop();
      //i = i + 1;
    }
    else{
      std:: cout << "Process" << i << "finished in queue 0!" << std::endl;
      q0.pop();
      //i = i + 1;
  }

  }
  // run Queue 1 and proecess 1 and maybe process 0
  else if(q0.size() == 0 && q1.size() != 0){
    int interrupt;
    for(int j = 0; j < q1.size(); j++){
    q1.front().bt,interrupt = calculate_runtime(q1.front().bt, i = 1);
    //update interupt
    if(interrupt == 1){q1.front().num_of_interrupts += 1;}
    //update exit time
    //send to next queue if not complete
    if(q1.front().bt != 0){
      q2.push(q1.front());
      q1.pop();
      //i = i + 1;
    }
    else{
      std:: cout << "Process finished in queue 1!" << std::endl;
      q1.pop();
    //i = i + 1;
  }
    }
  }
  else{

  }//FCFS function
  i = i + 1;
}

std::cout << "ready to enter MLFQ" << std::endl;

// display results
for(int i = 0; i < process_vec.size(); i++){
std:: cout << "Process:" << i << "has bt:" << process_vec[i].bt << std::endl;

}

/*
do
{
  process &temp0_qp = q0.front();
  std::cout << "executing process: " << temp0_qp.id <<" in Queue 0 for " << tq0 <<"\n\n";
  for (int i = 1; i < (tq0+1); i++)
  {
    temp0_qp.bt -= 1;
    temp0_qp.exit_time += 1;
    if(temp0_qp.bt == 0)
    {
      std::cout << temp0_qp.id <<" is interrupted " << temp0_qp.num_of_interrupts
                << "time, completes on queue #0, TAT for " << temp0_qp.id << " is "
                << temp0_qp.exit_time - temp0_qp.at << std::endl;
    }
    q0.
  }
  pop.
}
*/


return 0;
}

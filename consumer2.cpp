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



std:: cout << "my consumer recieved " << process_vec.size() << " process." <<std::endl;

std::queue<process> q0,q1,q2;
for(int i = 0; i < process_vec.size(); i++)
{
  q0.push(process_vec[i]);
}

int tq0{8};
int tq1{16};

std::cout << "ready to enter MLFQ" << std::endl;

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

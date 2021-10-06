#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <queue>

#include <sys/mman.h>
#include <iostream>

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
process P1;
process P2;

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

std::cout << "passed c string: ";
printf("%s",(char *)ptr);
std::cout << std::endl;

std::cout << "number of characters in array: " << strlen(ptr);
char c_array[strlen(ptr)];
sscanf(ptr,"%s",  c_array );


std::cout << "\n" << "extracting data........\n";

std::cout << std::endl;
std::string pid{""};
pid.push_back(c_array[0]);
pid.push_back(c_array[1]);

std::cout << "parsed data is the following: " << std::endl;
std::cout << "process id: " << pid << std::endl;

std::string a_time{""};
a_time.push_back(c_array[2]);

std::cout << "process arrival time: " << a_time << std::endl;

std::string b_time;
b_time.push_back(c_array[3]);
b_time.push_back(c_array[4]);
std::cout << "process burst time: " << b_time <<std::endl;

P1.id = pid;
P1.at = stoi(a_time);
P1.bt = stoi(b_time);
std::cout << P1.id <<std::endl;

std::cout << std::endl;
std::string pid2{""};
pid2.push_back(c_array[5]);
pid2.push_back(c_array[6]);

std::cout << "parsed data is the following: " << std::endl;
std::cout << "process id: " << pid2 << std::endl;

std::string a2_time{""};
a2_time.push_back(c_array[7]);

std::cout << "process arrival time: " << a2_time << std::endl;

std::string b2_time;
b2_time.push_back(c_array[8]);
b2_time.push_back(c_array[9]);
std::cout << "process burst time: " << b2_time <<std::endl;

P2.id = pid2;
P2.at = stoi(a2_time);
P2.bt = stoi(b2_time);
std::cout << P2.id <<std::endl;

// std::cout <<  *ptr << std::endl;

/* remove the shared memory object */

shm_unlink(name);

// MLFQ

std::queue<struct process> p0_queue;
p0_queue.push(P1);
p0_queue.push(P2);
std::queue<struct process> p1_queue;
std::queue<struct process> p2_queue;

// the processes enter multilevel queue
do
{
  //in queue 0:

  process &current0_process {p0_queue.front()};
  int tq0{8};


  std::cout << "executing process: " << current0_process.id << " in queue " << current0_process.qnum <<std::endl << std::endl;
  for(int i = 0; i < tq0; i++)
  {
    current0_process.bt = current0_process.bt - 1;

  }

  if(current0_process.id == "P1")
  {

    current0_process.exit_time = current0_process.exit_time + (2*tq0); // the 2 multiplier accounts for P2 tq in queue 0
    current0_process.num_of_interrupts++;
    p1_queue.push(current0_process);
  }

  if(current0_process.id == "P2")
  {
    current0_process.exit_time = current0_process.exit_time + (2*tq0) + 16; // the 2 accounts for P1 in queue 0 and 16 accounts for P1 tq  in queue 1
    current0_process.num_of_interrupts++;
    p1_queue.push(current0_process);

  }
  std::cout << "process " << current0_process.id << " has been interrupted, " << "total of interrupts so far: " << current0_process.num_of_interrupts << std::endl << std::endl;

  std::cout << "updating process: " << current0_process.id << std::endl;
  std::cout << " burst time after queue 0 is: "<< current0_process.bt << std::endl <<std::endl;
  std::cout << "current exit time of: " << current0_process.exit_time << std::endl << std::endl;

  p0_queue.pop();
} while (p0_queue.size() > 0 );

std::cout << "updated burst time of processes: " << p1_queue.front().id << " and " << p1_queue.back().id <<  std::endl;
std::cout << "now entering queue 1\n\n";

std::cout << p1_queue.front().bt << std::endl << std::endl;
std::cout << p1_queue.back().bt << std::endl << std::endl;


//entering queue 1:
do
{
  process &current1_process {p1_queue.front()};
  int tq1{16};
  int rm_time = current1_process.bt;

for(int i = 0; i < tq1; i++)
{
  current1_process.bt = current1_process.bt - 1;

  if(current1_process.bt == 0)
  {
     current1_process.exit_time = current1_process.exit_time + i;

    std::cout << current1_process.id << " is interrupted " << current1_process.num_of_interrupts
              << " time, completes on queue #1, TAT for "  << current1_process.id << " is "
              << current1_process.exit_time - current1_process.at << std::endl;
     i = 15;

     continue;
  }
}

  if(current1_process.id == "P1")
  {
    current1_process.exit_time = current1_process.exit_time + tq1 + 2; // the two is for P2 remaind time in queue 1
    current1_process.num_of_interrupts++;
    p2_queue.push(current1_process);
  }
  std::cout << "process " << current1_process.id << " has been interrupted, " << "total of interrupts so far: " << current1_process.num_of_interrupts << std::endl << std::endl;

  std::cout << "updating process: " << current1_process.id << std::endl;
  std::cout << " burst time after queue 1 is: "<< current1_process.bt << std::endl <<std::endl;
  p1_queue.pop();

} while (p1_queue.size() > 0);



std::cout << "entering queue 2" <<std::endl;

std::cout << p2_queue.front().id << std::endl;
do
{
  process &current2_process{p2_queue.front()};
  int time_left = current2_process.bt;
  for(int i = 0; i < time_left; i++)
  {
    current2_process.bt = current2_process.bt - 1;
    if(current2_process.bt == 0)
    {
      current2_process.exit_time = current2_process.exit_time + i;

    std::cout << current2_process.id << " is interrupted " << current2_process.num_of_interrupts
              << " times, completes on queue #2, TAT for "  << current2_process.id << " is "
              << current2_process.exit_time - current2_process.at << std::endl;
    }
  }
  p2_queue.pop();
} while (p2_queue.size() > 0);






return 0;
}

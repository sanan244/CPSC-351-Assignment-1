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
#include <algorithm>

struct process
{
  std::string id{""};
  int at{0};
  int bt{0};
  int qnum{0};
  int exit_time{1};
  int num_of_interrupts{0};
};

bool cmpArrivalTime(const process& a, const process& b)
{
  return a.at < b.at;
}

int main()
{
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
  ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  /* read from the shared memory object */

  std::vector<process> process_vec;

  std::cout << "passed c string: ";
  printf("%s", (char *)ptr);
  std::cout << std::endl;
  const char *delim{","};
  char *token = strtok(ptr, delim);
  std::cout << "our first process has a pid of: " << token << std::endl;

  while (token != NULL)
  {
    process temp_process;

    temp_process.id = token;

    token = strtok(NULL, delim);

    temp_process.at = atoi(token);

    token = strtok(NULL, delim);

    temp_process.bt = atoi(token);
    process_vec.push_back(temp_process);

    token = strtok(NULL, delim);
  }

  // Sort vector by arrival time
  std::sort(process_vec.begin(), process_vec.end(), cmpArrivalTime);

  std::cout << "my consumer recieved " << process_vec.size() << " process." << std::endl;

  std::queue<process> q0, q1, q2;
  for (int i = 0; i < process_vec.size(); i++)
  {
    q0.push(process_vec[i]);
  }

  int tq0{8};
  int tq1{16};
  int complete_time = 0;

  std::cout << "ready to enter MLFQ\n\n";

  do
  {
    //in queue 0:

    process &current0_process{q0.front()};
    int tq0{8};

    std::cout << "executing process: " << current0_process.id << " in queue 0 for "
              <<  tq0 <<std::endl;

    std::cout << "updating process information.......................................\n\n";
    for (int i = 0; i < tq0; i++)
    {
      current0_process.bt = current0_process.bt - 1;
      complete_time++;
    }

      current0_process.exit_time = complete_time;
      current0_process.num_of_interrupts++;
      q1.push(current0_process);

    std::cout << "process " << current0_process.id << " has been interrupted, "
              << "total of interrupts so far: " << current0_process.num_of_interrupts << std::endl
              << std::endl;

    std::cout << "updating process: " << current0_process.id << std::endl;
    std::cout << " burst time after queue 0 is: " << current0_process.bt << std::endl
              << std::endl;
    std::cout << "current exit time of: " << current0_process.exit_time << std::endl
              << std::endl;

    q0.pop();
  } while (q0.size() > 0);

  std::cout << "updated burst time of processes: " << q1.front().id << " and " << q1.back().id << std::endl;
  std::cout << "now entering queue 1\n\n";


  //entering queue 1:
  do
  {
    process &current1_process{q1.front()};
    int tq1{16};

    std::cout << "executing process: " << current1_process.id << " in queue 1 for "
              <<  tq1 <<std::endl;

    std::cout << "updating process information.......................................\n\n";

    for (int i = 0; i < tq1; i++)
    {
      current1_process.bt = current1_process.bt - 1;
      complete_time++;

      if (current1_process.bt == 0)
      {
        current1_process.exit_time = complete_time;

        std::cout << current1_process.id << " is interrupted " << current1_process.num_of_interrupts
                  << " time, completes on queue #1, TAT for " << current1_process.id << " is "
                  << current1_process.exit_time - current1_process.at << std::endl;
        i = 15;

        continue;
      }
    }

      current1_process.exit_time = complete_time;
      current1_process.num_of_interrupts++;
      q2.push(current1_process);
    
    std::cout << "process " << current1_process.id << " has been interrupted, "
              << "total of interrupts so far: " << current1_process.num_of_interrupts << std::endl
              << std::endl;

    std::cout << "updating process: " << current1_process.id << std::endl;
    std::cout << " burst time after queue 1 is: " << current1_process.bt << std::endl
              << std::endl;
    q1.pop();

  } while (q1.size() > 0);

  std::cout << "entering queue 2" << std::endl;

  do
  {
    process &current2_process{q2.front()};
    int time_left = current2_process.bt;

    for (int i = 0; i < time_left; i++)
    {
      current2_process.bt = current2_process.bt - 1;
      complete_time++;
      if (current2_process.bt == 0)
      {
        current2_process.exit_time = complete_time;

        std::cout << current2_process.id << " is interrupted " << current2_process.num_of_interrupts
                  << " times, completes on queue #2, TAT for " << current2_process.id << " is "
                  << current2_process.exit_time - current2_process.at << std::endl;
      }
    }
    q2.pop();
  } while (q2.size() > 0);

  return 0;
}

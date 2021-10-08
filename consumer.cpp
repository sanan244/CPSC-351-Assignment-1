#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <queue>
#include <iostream>
#include <string>
#include <algorithm>

// A struct for a process object which holds all of the elements of a process (ID, Arrival Time, Burst Time, etc.)
struct process
{
  std::string id{""};
  int at{0};
  int bt{0};
  int qnum{0};
  int exit_time{1};
  int num_of_interrupts{0};
};

// A comparison function for sorting the arrival times of processes
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

  // A vector for holding processes
  std::vector<process> process_vec;

  std::cout << "passed c string: ";
  printf("%s", (char *)ptr);
  std::cout << std::endl;
  const char *delim{","};
  char *token = strtok(ptr, delim);
  std::cout << "our first process has a pid of: " << token << std::endl;

  // Parses the data passed from producer to the process vector
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

  // Sorts vector by arrival time (from lowest to highest arrival number)
  std::sort(process_vec.begin(), process_vec.end(), cmpArrivalTime);

  // Confirms the number of processes the user passed from producer
  std::cout << "my consumer recieved " << process_vec.size() << " process." << std::endl;

  // 3 Queues 
  std::queue<process> q0, q1, q2;

  // Pushes each process in the process vector onto the first queue (q0)
  for (int i = 0; i < process_vec.size(); i++)
  {
    q0.push(process_vec[i]);
  }

  int tq0{8}; // Amount of time in milliseconds a process is given in q0
  int tq1{16}; // Amount of time in milliseconds a process is given in q1
  int complete_time = 0; // Amount of time a process takes to complete

  // Confirms that the processes are now entering the multi-level feedback queue (MLFQ)
  std::cout << "ready to enter MLFQ" << std::endl << std::endl;

  std::cout << "entering queue 0" << std::endl;
  std::cout << "----------------" << std::endl;
  do
  {
    //in queue 0:

    process &current0_process{q0.front()};

    std::cout << "executing process: " << current0_process.id << " in queue 0 for "
              <<  tq0 <<std::endl;

    std::cout << "updating process information.......................................\n\n";
    // If the burst time (bt) of process is greater than tq0, subtract tq0 from bt
    if (current0_process.bt > tq0)
    {
      for (int i = 0; i < tq0; i++)
      {
        current0_process.bt = current0_process.bt - 1;
        complete_time++;
      }

      current0_process.num_of_interrupts++; // Since bt is not 0 after passing through q0, process is interrupted
      current0_process.exit_time = complete_time;
      std::cout << "process " << current0_process.id << " has been interrupted, "
      << "total of interrupts so far: " << current0_process.num_of_interrupts << std::endl
      << std::endl;

      q1.push(current0_process); // Push this process to q1 since it is not finished (bt is not 0)

      // Update on progress
      std::cout << "updating process: " << current0_process.id << std::endl;
      std::cout << " burst time after queue 0 is: " << current0_process.bt << std::endl
      << std::endl;
      std::cout << "current exit time of: " << current0_process.exit_time << std::endl
      << std::endl;
    }
    // If bt of process was less than tq0, bt is 0
    else
    {
      complete_time += current0_process.bt;
      current0_process.exit_time = complete_time;
      current0_process.bt = 0;

      // Since bt is 0, process finished on q0
      std::cout << current0_process.id << " is interrupted " << current0_process.num_of_interrupts
      << " times, completes on queue #0, TAT for " << current0_process.id << " is "
      << current0_process.exit_time - current0_process.at << std::endl << std::endl;
    }

    // Remove this process from q0
    q0.pop();
  } while (q0.size() > 0); // q0 must be empty before processes can move through next queue (q1)

  // If q1 has processes, continue to q1 in program
  if(q1.size() > 0)
  {
    std::cout << std::endl;
    std::cout << "entering queue 1" << std::endl;
    std::cout << "----------------" << std::endl;
  }

  //entering queue 1:
  while(q1.size() > 0)
  {
    process &current1_process{q1.front()};

    std::cout << "executing process: " << current1_process.id << " in queue 1 for "
              <<  tq1 <<std::endl;

    std::cout << "updating process information.......................................\n\n";

    // If bt of process is greater than tq1, subtract tq1 from bt
    if (current1_process.bt > tq1)
    {
      for (int i = 0; i < tq1; i++)
      {
        current1_process.bt = current1_process.bt - 1;
        complete_time++;
      }

      current1_process.num_of_interrupts++; // Since bt is not 0 after passing through q1, process is interrupted
      current1_process.exit_time = complete_time;
      std::cout << "process " << current1_process.id << " has been interrupted, "
      << "total of interrupts so far: " << current1_process.num_of_interrupts << std::endl
      << std::endl;

      q2.push(current1_process); // Push this process to q2 since it is not finished (bt is not 0)

      // Update on progress
      std::cout << "updating process: " << current1_process.id << std::endl;
      std::cout << " burst time after queue 1 is: " << current1_process.bt << std::endl
      << std::endl;
      std::cout << "current exit time of: " << current1_process.exit_time << std::endl
      << std::endl;
    }
    // If bt of process was less than tq1, bt is 0
    else
    {
      complete_time += current1_process.bt;
      current1_process.exit_time = complete_time;
      current1_process.bt = 0;

      // Since bt is 0, process finished on q1
      std::cout << current1_process.id << " is interrupted " << current1_process.num_of_interrupts
      << " time, completes on queue #1, TAT for " << current1_process.id << " is "
      << current1_process.exit_time - current1_process.at << std::endl << std::endl;
    }
    
    // Remove this process from q1
    q1.pop();
  }

  // If q2 has processes, continue to q2 in program
  if(q2.size() > 0)
  {
    std::cout << std::endl;
    std::cout << "entering queue 2" << std::endl;
    std::cout << "----------------" << std::endl;
  }

  // Entering queue 2
  while(q2.size() > 0)
  {
    process &current2_process{q2.front()};

    // Amount of time left for current process
    int time_left = current2_process.bt;

    // Any remaining processes are finished regardless of remaining bt
    for (int i = 0; i < time_left; i++)
    {
      current2_process.bt = current2_process.bt - 1;
      complete_time++;
      if (current2_process.bt == 0)
      {
        current2_process.exit_time = complete_time;

        // Process is finished and update
        std::cout << current2_process.id << " is interrupted " << current2_process.num_of_interrupts
                  << " times, completes on queue #2, TAT for " << current2_process.id << " is "
                  << current2_process.exit_time - current2_process.at << std::endl;
      }
    }

    // Remove this process from q2
    q2.pop();
  }

  return 0;
}

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

  struct process
  {
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
  ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  /* read from the shared memory object */

  std::vector<process> process_vec;

  std::cout << "passed c string: ";
  printf("%s", (char *)ptr);
  std::cout << std::endl;
  const char *delim{","};
  char *token = strtok(ptr, delim);
  std::cout << "our first process has a pid of: " << token << std::endl;
  //std::cout << "parsed tokens are the following\n";

  while (token != NULL)
  {
    process temp_process;

   // std::cout << token << std::endl;
    temp_process.id = token;

    token = strtok(NULL, delim);

    //std::cout << token << std::endl;
    temp_process.at = atoi(token);

    token = strtok(NULL, delim);

    //std::cout << token << std::endl;
    temp_process.bt = atoi(token);
    process_vec.push_back(temp_process);

    token = strtok(NULL, delim);
  }

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
      //std::cout << complete_time << std::endl;
    }

    // if (current0_process.id == "P1")
    // {
      // complete_time += tq0;
      current0_process.exit_time = complete_time;
      // current0_process.exit_time = current0_process.exit_time + (2 * tq0); // the 2 multiplier accounts for P2 tq in queue 0
      current0_process.num_of_interrupts++;
      q1.push(current0_process);
    // }

    // if (current0_process.id == "P2")
    // {
    //   current0_process.exit_time = current0_process.exit_time + (2 * tq0) + 16; // the 2 accounts for P1 in queue 0 and 16 accounts for P1 tq  in queue 1
    //   current0_process.num_of_interrupts++;
    //   q1.push(current0_process);
    // }
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
        // current1_process.exit_time = current1_process.exit_time + i;

        std::cout << current1_process.id << " is interrupted " << current1_process.num_of_interrupts
                  << " time, completes on queue #1, TAT for " << current1_process.id << " is "
                  << current1_process.exit_time - current1_process.at << std::endl;
        i = 15;

        continue;
      }
    }

    // if (current1_process.id == "P1")
    // {
      // complete_time += tq1;
      current1_process.exit_time = complete_time;
      // current1_process.exit_time = current1_process.exit_time + tq1 + 2; // the two is for P2 remaind time in queue 1
      current1_process.num_of_interrupts++;
      q2.push(current1_process);
    // }
    std::cout << "process " << current1_process.id << " has been interrupted, "
              << "total of interrupts so far: " << current1_process.num_of_interrupts << std::endl
              << std::endl;

    std::cout << "updating process: " << current1_process.id << std::endl;
    std::cout << " burst time after queue 1 is: " << current1_process.bt << std::endl
              << std::endl;
    q1.pop();

  } while (q1.size() > 0);

  std::cout << "entering queue 2" << std::endl;

  //std::cout << q2.front().id << std::endl;
  do
  {
    process &current2_process{q2.front()};
    int time_left = current2_process.bt;

    //std::cout << "updating process information.......................................\n\n";

    for (int i = 0; i < time_left; i++)
    {
      current2_process.bt = current2_process.bt - 1;
      complete_time++;
      if (current2_process.bt == 0)
      {
        // complete_time += i;
        current2_process.exit_time = complete_time;
        // current2_process.exit_time = current2_process.exit_time + i;

        std::cout << current2_process.id << " is interrupted " << current2_process.num_of_interrupts
                  << " times, completes on queue #2, TAT for " << current2_process.id << " is "
                  << current2_process.exit_time - current2_process.at << std::endl;
      }
    }
    q2.pop();
  } while (q2.size() > 0);

  // do
  // {
  //   process &temp0_qp = q0.front();
  //   std::cout << "executing process: " << temp0_qp.id <<" in Queue 0 for " << tq0 <<"\n\n";
  //   for (int i = 1; i < (tq0+1); i++)
  //   {
  //     temp0_qp.bt -= 1;
  //     temp0_qp.exit_time += 1;
  //     if(temp0_qp.bt == 0)
  //     {
  //       std::cout << temp0_qp.id <<" is interrupted " << temp0_qp.num_of_interrupts
  //                 << "time, completes on queue #0, TAT for " << temp0_qp.id << " is "
  //                 << temp0_qp.exit_time - temp0_qp.at << std::endl;
  //     }
  //     q0.
  //   }
  //   pop
  // }

  return 0;
}

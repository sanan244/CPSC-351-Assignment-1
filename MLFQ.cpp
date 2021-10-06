#include <iostream>
#include <string>
#include <queue>

int main()
{
  struct process{
std::string id{""};
int at{0};
int bt{0};
int qnum{0};
int exit_time{0};
int num_of_interrupts{0};
};

struct process P1;
P1.id = "P1";
P1.at = 0;
P1.bt = 40;

struct process P2;
P2.id = "P2";
P2.at = 2;
P2.bt = 10;

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

    current0_process.exit_time = current0_process.exit_time + (2*tq0); // this accounts for P2 tq in queue 0
    current0_process.num_of_interrupts++;
    p1_queue.push(current0_process);
  }

  if(current0_process.id == "P2")
  {
    current0_process.exit_time = current0_process.exit_time + tq0 + 16; // the 16 accounts for P1 tq  in queue 1
    current0_process.num_of_interrupts++;
    p1_queue.push(current0_process);

  }
  std::cout << "process " << current0_process.id << " has been interrupted, " << "total of interrupts so far: " << current0_process.num_of_interrupts << std::endl << std::endl;

  std::cout << "updating process: " << current0_process.id << std::endl;
  std::cout << " burst time after queue 0 is: "<< current0_process.bt << std::endl <<std::endl;
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
for(int i = 0; i < tq1; i++)
{
  current1_process.bt = current1_process.bt - 1;

  if(current1_process.bt == 0)
  { current1_process.exit_time = current1_process.exit_time + i;

    std::cout << current1_process.id << " is interrupted " << current1_process.num_of_interrupts
              << " time, completes on queue #1, TAT for "  << current1_process.id << " is "
              << current1_process.exit_time - current1_process.at << std::endl;
     i = 15;

     continue;
  }
}

  if(current1_process.id == "P1")
  {
    current1_process.exit_time = current1_process.exit_time + tq1;
    current1_process.num_of_interrupts++;
    p2_queue.push(current1_process);
  }
  std::cout << "process " << current1_process.id << " has been interrupted, " << "total of interrupts so far: " << current1_process.num_of_interrupts << std::endl << std::endl;

  std::cout << "updating process: " << current1_process.id << std::endl;
  std::cout << " burst time after queue 0 is: "<< current1_process.bt << std::endl <<std::endl;
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

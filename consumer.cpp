#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include <sys/mman.h>
#include <iostream>

int main()
{

struct process{
std::string id{""};
int at{0};
int bt{0};
int qnum{0};
};
process P1;

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
return 0;
}

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

std::cout << "passed c string: ";
printf("%s",(char *)ptr);
std::cout << std::endl;


return 0;
}

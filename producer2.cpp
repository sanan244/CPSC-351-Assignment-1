#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string>
#include <iostream>


#include <sys/mman.h>

int main(int argc, char* argv[])
{
  /* the size (in bytes) of shared memory object */
const int SIZE = 4096;
/* name of the shared memory object */
const char *name = "Shared Memory";



/* calculates the number of process */
int num_args = argc -1; // argc include the argument a.out so we subtract it out
int num_process = (num_args/3); //since process come with 3 parameter we divide by 3 to get corrent number of process given
std::cout << "number of process given: " << num_process <<std::endl;
std::string str_num_p = std::to_string(num_process);
str_num_p.push_back(',');
const char *p_count;
p_count = str_num_p.c_str();
std::cout << p_count << std::endl;
std::cout << "number of of commandline arguments: " << num_args << std::endl;


/* shared memory file descriptpr */
int fd;
//pointer to shared memory objcet
char *ptr;

fd = shm_open(name, O_CREAT | O_RDWR, 0666);
ftruncate(fd, SIZE);

ptr = (char*) mmap(0, SIZE, PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);

sprintf(ptr,"%s", p_count);
ptr+= strlen(p_count);

for(int i = 1;i < argc; i++)
{
  sprintf(ptr,"%s",argv[i]);
  ptr += strlen(argv[i]);
}


printf("%s","wrote to shared memmory");

getchar();

return 0;
}

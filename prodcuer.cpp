#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include <sys/mman.h>

int main(int argc, char* argv[]){
  /* the size (in bytes) of shared memory object */
const int SIZE = 4096;
/* name of the shared memory object */
const char *name = "Shared Memory";
const char *pid1 = argv[1];
const char *at1  = argv[2];
const char *bt1  = argv[3];
const char *pid2 = argv[4];
const char *at2  = argv[5];
const char *bt2  = argv[6];

/* shared memory file descriptpr */
int fd;
//pointer to shared memory objcet
char *ptr;

fd = shm_open(name, O_CREAT | O_RDWR, 0666);
ftruncate(fd, SIZE);

ptr = (char*) mmap(0, SIZE, PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);

sprintf(ptr,"%s",pid1);

ptr += strlen(pid1);

sprintf(ptr,"%s",at1);

ptr += strlen(at1);

sprintf(ptr,"%s",bt1);
ptr += strlen(bt1);

sprintf(ptr,"%s",pid2);
ptr += strlen(pid2);

sprintf(ptr,"%s",at2);
ptr += strlen(at2);

sprintf(ptr,"%s",bt2);
ptr += strlen(bt2);

printf("%s","wrote to shared memmory");

getchar();

return 0;
}

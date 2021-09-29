#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>

using namespace std;

class P;

int main(){

    const int SIZE = 4096;
    const char *name = "OS";
    int shm_fd;
    char *ptr;

    //prompt for input size
   int input_size;
   int i;

   cout << "Enter the size of input\n";
   cin >> input_size;

   P user_input[input_size];

   for (i = 0; i < input_size; i++) {
      // Reading User Input sales value Based on index
    cout << "Enter Value for ID " << i << " : ";
    cin >> user_input[i].ID;

    cout << "Enter Value for AT " << i << " : ";
    cin >> user_input[i].AT;

    cout << "Enter Value for BT " << i << " : ";
    cin >> user_input[i].BT;
   }

   cout << "\n User Input Values\n";
   for (i = 0; i < 12; i++) {
      // Accessing sales value using for loop
    cout << "Position : " << i << " , ID Value : " << user_input[i].ID << " \n";
    cout << "Position : " << i << " , AT Value : " << user_input[i].AT << " \n";
    cout << "Position : " << i << " , BT Value : " << user_input[i].BT << " \n";
   }

// shm_fd = shm_open(name,O_RDONLY, 0666);

// ptr = (char*)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

// printf("%s", (char *)ptr);

// shm_unlink(name);
return 0;

}

class P {
    public:
        string ID;
        int AT;
        int BT;
};
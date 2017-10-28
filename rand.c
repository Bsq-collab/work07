#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

// The 2 tab formatting here would make Linus Torvalds cry

// Universal rand pipe index,
// so we don't reopen and close our rand file every time we read
int RAND_FILE;

// File name of our new file to write to
const char *READ_FILE_NAME = "numeros";

// Get a random integer from our rand pipe
int get_rand_int() {
  int ans;
  read(RAND_FILE,&ans,sizeof(int));
  return ans;
}


int main() {
  // Initialize our rand file
  RAND_FILE = open("/dev/random",O_RDONLY);
  if (RAND_FILE == -1) {
      printf("ERROR Your rand file is invalid!\n");
      printf("Value of errno: %d\n", errno);
      printf("Error type: %s\n", strerror(errno) );
      return 0x00F;
  }

  // Populate our first array with random numbers
  int nums[10];
  int i=0;
  printf("populating numbers.......\n");
  while (i<10){
    nums[i]=get_rand_int();
    printf("added  to index %d: %d\n",i,nums[i]);
    i+=1;
  }

  // Write our data to a file
  // Will not include error checking here, because if you mess up here
  // then you're using the open function incorrectly
  int numbers= open(READ_FILE_NAME, O_CREAT | O_WRONLY,0644);
  write(numbers,nums,sizeof(nums));
  close(numbers);

  // Store our read values from the written file
  int newArr[10];

  // Will not include error checking here, because if you mess up here
  // then you're using the open function incorrectly
  numbers=open(READ_FILE_NAME,O_RDONLY,0644);
  read(numbers,newArr,sizeof(newArr));

  // Show read values with error check
  i=0;
  printf("printing new array with error check....\n");
  while(i<10){
    printf("index %d:%d, error: %d\n",i,newArr[i], newArr[i] - nums[i]);
    i+=1;
  }
  return 0;

}

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int get_rand_int(){
  int ans;
  int random=open("/dev/random",O_RDONLY);
  read(random,&ans,sizeof(int));
  close(random);
  return ans;
}

int main(){
  int nums[10];
  int i=0;
  printf("populating numbers.......\n");
  while (i<10){
    nums[i]=get_rand_int();
    printf("added  to index %d: %d\n",i,nums[i]);
    i+=1;
  }

  int numbers= open("numeros", O_CREAT | O_RDWR,0644);
  write(numbers,nums,sizeof(nums));
  close(numbers);

  
  int newArr[10];
  
  numbers=open("numeros",O_RDONLY,0644);
  read(numbers,newArr,sizeof(newArr));

  i=0;
  printf("printing new array....\n");
  while(i<10){
    printf("index %d:%d\n",i,newArr[i]);
    i+=1;
  }
  return 0;

}

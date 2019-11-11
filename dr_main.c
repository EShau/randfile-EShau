#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

typedef unsigned long size_t;

size_t convertToNumber(char * array, int n){
  size_t number = 0;
  size_t power = 1;
  while (n){
    int digit = array[n] > 0 ? array[n] : array[n] * -1;
    digit = digit % 10;
    number += digit * power;
    power *= 10;
    n--;
  }
  return number;
}

size_t generate_random(int bytes){
  char buffer[bytes];
  int fd = open("/dev/random",O_RDONLY);
  // printf("%d\n",fd);
  // printf("%s\n",strerror(errno));
  read(fd, buffer, sizeof(buffer));
  close(fd);
  size_t i = convertToNumber(buffer, bytes);
  return i;
}

int main(){
  int i = 0;
  unsigned int length = 10;
  size_t random_numbers[10];
  printf("Generating random numbers:\n");
  for (i = 0; i < 10; i++){
    random_numbers[i] = generate_random(length);
    printf("\trandom %d: %lu\n", i, random_numbers[i]);
  }
  printf("\n");
  printf("Writing numbers to file...\n\n");
  int fd = open("testfile", O_WRONLY | O_CREAT | O_TRUNC, 0760);
  // printf("%d\n",fd);
  // printf("%s\n",strerror(errno));
  write(fd, random_numbers, sizeof(random_numbers));
  close(fd);
  printf("Reading numbers to file...\n\n");
  size_t random_numbers2[10];
  fd = open("testfile", O_RDONLY);
  // printf("%d\n",fd);
  // printf("%s\n",strerror(errno));
  read(fd, random_numbers2, sizeof(random_numbers2));
  close(fd);
  printf("Verification that written values were the same:\n");
  for (i = 0; i < 10; i++){
    printf("\trandom %d: %lu\n", i, random_numbers2[i]);
  }
  return 0;
}

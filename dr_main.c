#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

unsigned char * generate_random(unsigned char bytes){
  int i;
  unsigned char buffer[bytes];
  int file = open("/dev/random",O_RDONLY);
  read(file, buffer, sizeof(buffer));
  close(file);
  for (i = 0; i < 10; i++){
    printf("%c",*(buffer + i));
  }
  printf("\n");
  return buffer;
}

int main(){
  int i;
  unsigned int length = 10;
  unsigned char * random_number;
  random_number = generate_random(length);
  for (i = 0; i < 10; i++){
    printf("%c",*(random_number + i));
  }
  printf("\n");
  return 0;
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "usage: sleep ticks\n");
    exit(1);
  }

  int ticks = atoi(argv[1]);
  if(ticks < 0){
    fprintf(2, "sleep: ticks must be non-negative\n");
    exit(1);
  }

  sleep(ticks);
  printf("sleep %d\n", ticks);
  exit(0);
}

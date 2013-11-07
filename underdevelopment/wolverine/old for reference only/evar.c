#include <stdio.h>
#include <stdlib.h>

int main(void){
  printf("DB2INSTANCE : %s\n", getenv("DB2INSTANCE"));
  return 0;
}

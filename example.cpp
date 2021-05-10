#include "example.h"
#include <stdbool.h> // for bool
#include <stdio.h>   // for printf

int main()
{
  List myList = newList();
  myList.destroy(&myList, 5);
  printf("%d", myList.id);
  return 0;
}
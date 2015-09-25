#include <stdlib.h>
#include <stdio.h>

void*	xmalloc(int size)
{
  void	*res;

  res = malloc(size);
  if (res == NULL)
    {
      printf("Memory allocation fail !\n");
      exit(EXIT_FAILURE);
    }
  return (res);
}

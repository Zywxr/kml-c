#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

int error(char *msg, char *value) {
  if (msg == NULL) {
    error("You failed your error message.", NULL);
    return (FAILURE);
  }
  if (value != NULL)
    printf("Error: %s (%s).\n", msg, value);
  else
    printf("Error: %s.\n", msg);
  return (FAILURE);
}

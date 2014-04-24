#pragma once

#include <stdlib.h>

double rand01 ()
{
  return rand () / (double)RAND_MAX;
}

double rand11 ()
{
  return 2 * rand01 () - 1;
}
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

void main (int __argc, char *__argv[])
{
  FreeConsole ();

  srand (time (NULL));

  Init (&__argc, __argv);
}

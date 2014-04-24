#pragma once

#include <time.h>

class timer
{
  double GlobalTime, SyncTime, PauseTime, DeltaTime;
  time_t StartClocks, PauseClocks, LastClocks;
  bool IsPause;

public:
  timer (bool started = true, double globaltime = 0) : GlobalTime (globaltime), SyncTime (0), PauseTime (0),
                                                       IsPause (!started), PauseClocks (0), DeltaTime (0)
  {
    StartClocks = LastClocks = clock ();
  }

  void update ()
  {
    time_t t = clock ();

    GlobalTime = (t - StartClocks) / (double)CLOCKS_PER_SEC;
    if (IsPause)
    {
      PauseClocks += t - LastClocks;
      PauseTime = PauseTime / (double)CLOCKS_PER_SEC;
    }

    double tmp = (t - StartClocks - PauseClocks) / (double)CLOCKS_PER_SEC;

    DeltaTime = tmp - SyncTime;
    SyncTime = tmp;
    LastClocks = t;
  }

  double getGlobalTime ()
  {
    return GlobalTime;
  }

  double getSyncTime ()
  {
    return SyncTime;
  }

  double getDeltaTime ()
  {
    return DeltaTime;
  }

  bool getIsPause ()
  {
    return IsPause;
  }

  void switchPause ()
  {
    IsPause = !IsPause;
  }
};
#pragma once

#include <vector>

#include "vec.h"
#include "grav.h"

using namespace std;

class molecule 
{
  double mass;
  vec<double> Pos, Speed, newPos, newSpeed;

public:

  vec<double> getPos ()
  {
    return Pos;
  }

  vec<double> getSpeed ()
  {
    return Speed;
  }

  molecule (double m, vec<double> P, vec<double> S = vec<double> ()) 
    : Pos (P), mass (m), Speed (S)
  {}

  void move (vector<molecule> m, double delta_t)
  {
    vec<double> newPos;

    molecule::newPos = molecule::Pos + molecule::Speed * delta_t;
    molecule::newSpeed = molecule::Speed;

    for (unsigned int i = 0; i < m.size(); i++)
    {
      vec<double> tmp = m[i].Pos - molecule::Pos;

      if (tmp.len2() != 0)
      {
        tmp *= G * delta_t * m[i].mass / tmp.len2();
        molecule::newPos += tmp * delta_t / 2;
        molecule::newSpeed += tmp;
      }
    }
  }

  void update ()
  {
    molecule::Pos = molecule::newPos;
    molecule::Speed = molecule::newSpeed;
  }
};

#pragma once

#include <cmath>

#include <assert.h>

#include "rand.h"

template<typename T = double>
  class vec
  {
  public:
    T x, y, z;

    vec (T X = 0, T Y = 0, T Z = 0) : x (X), y (Y), z (Z)
    {}

    vec<T> &random ()
    {
      do
      {
        x = rand11 ();
        y = rand11 ();
        z = rand11 ();
      } while (len2 () > 1);

      return *this;
    }

    T len2 () const
    {
      return x * x + y * y + z * z;
    }

    T len () const
    {
      return sqrt(x * x + y * y + z * z);
    }

    vec<T> operator+ (const vec a) const
    {
      return vec<T> (x + a.x, y + a.y, z + a.z);
    }

    vec<T> &operator+= (const vec a)
    {
      vec<T> tmp (x + a.x, y + a.y, z + a.z);

      return *this = tmp;
    }

    vec<T> operator- () const
    {
      return vec<T> (-x, -y, -z);
    }

    vec<T> operator- (const vec a) const
    {
      return vec<T> (x - a.x, y - a.y, z - a.z);
    }

    vec<T> &operator-= (const vec a)
    {
      vec<T> tmp (x - a.x, y - a.y, z - a.z);

      return *this = tmp;
    }

    vec<T> &operator= (const vec a)
    {
      x = a.x;
      y = a.y;
      z = a.z;

      return *this;
    }

    bool operator> (const vec a) const
    {
      return len2 () > a.len2 ();
    }

    bool operator>= (const vec a) const
    {
      return len2 () >= a.len2 ();
    }

    bool operator< (const vec a) const
    {
      return len2 () < a.len2 ();
    }

    bool operator<= (const vec a) const
    {
      return len2 () <= a.len2 ();
    }

    T operator& (const vec a) const
    {
      return x * a.x + y * a.y + z * a.z;
    }

    vec<T> operator% (const vec a) const
    {
      return vec<T> (y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
    }

    vec<T> &operator%= (const vec a)
    {
      vec<T> tmp(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);

      return *this = tmp;
    }

    vec<T> operator* (T a) const
    {
      return vec<T> (x * a, y * a, z * a);
    }

    vec<T> &operator*= (T a)
    {
      x *= a;
      y *= a;
      z *= a;

      return *this;
    }

    vec<T> operator/ (T a) const
    {
      assert (a != 0);

      return vec<T> (x / a, y / a, z / a);
    }

    vec<T> &operator/= (T a)
    {
      assert (a != 0);

      x /= a;
      y /= a;
      z /= a;

      return *this;
    }

    vec<T> Normalising () const
    {
      return *this / len ();
    }

    vec<T> &Normalise ()
    {
      *this / len ();

      return *this;
    }
  };

template<class T = double>
  vec<T> vecgenerate ()
  {
    return vec<T>().random ();
  }

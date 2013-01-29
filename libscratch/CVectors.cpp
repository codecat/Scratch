/*  libscratch - Multipurpose objective C++ library.
    Copyright (C) 2012 - 2013  Angelo Geels

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "CVectors.h"

Vector3f::Vector3f(void)
{
  x = y = z = 0.0f;
}

Vector3f::Vector3f(FLOAT f)
{
  x = y = z = f;
}

Vector3f::Vector3f(FLOAT fX, FLOAT fY, FLOAT fZ)
{
  x = fX;
  y = fY;
  z = fZ;
}

Vector3f::~Vector3f(void)
{
}

void Vector3f::ClampX(const FLOAT min, const FLOAT max)
{
  if(x < min) {
    x = min;
  } else if(x > max) {
    x = max;
  }
}

void Vector3f::ClampY(const FLOAT min, const FLOAT max)
{
  if(y < min) {
    y = min;
  } else if(y > max) {
    y = max;
  }
}

void Vector3f::ClampZ(const FLOAT min, const FLOAT max)
{
  if(z < min) {
    z = min;
  } else if(z > max) {
    z = max;
  }
}

FLOAT Vector3f::Angle(const Vector3f &vOrigin)
{
  return atan2(y-vOrigin.y, x-vOrigin.x);
}

FLOAT Vector3f::Length(void)
{
  return sqrt(x*x + y*y + z*z);
}

FLOAT Vector3f::Dot(const Vector3f &v2)
{
  return x*v2.x + y*v2.y + z*v2.z;
}

Vector3f Vector3f::operator +(const Vector3f &v)
{
  return Vector3f(x+v.x, y+v.y, z+v.z);
}

Vector3f Vector3f::operator -(const Vector3f &v)
{
  return Vector3f(x-v.x, y-v.y, z-v.z);
}

Vector3f Vector3f::operator *(const Vector3f &v)
{
  return Vector3f(x*v.x, y*v.y, z*v.z);
}

Vector3f Vector3f::operator *(const FLOAT f)
{
  return Vector3f(x*f, y*f, z*f);
}

Vector3f Vector3f::operator /(const Vector3f &v)
{
  return Vector3f(x/v.x, y/v.y, z/v.z);
}

Vector3f Vector3f::operator /(const FLOAT f)
{
  return Vector3f(x/f, y/f, z/f);
}

BOOL Vector3f::operator ==(const Vector3f &v)
{
  return x==v.x && y==v.y && z==v.z;
}

BOOL Vector3f::operator !=(const Vector3f &v)
{
  return !operator==(v);
}

Vector3f& Vector3f::operator +=(const Vector3f &v)
{
  x += v.x;
  y += v.y;
  z += v.z;

  return *this;
}

Vector3f& Vector3f::operator -=(const Vector3f &v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;

  return *this;
}

Vector3f& Vector3f::operator *=(const Vector3f &v)
{
  x *= v.x;
  y *= v.y;
  z *= v.z;

  return *this;
}

Vector3f& Vector3f::operator *=(const FLOAT f)
{
  x *= f;
  y *= f;
  z *= f;

  return *this;
}

Vector3f& Vector3f::operator /=(const Vector3f &v)
{
  x /= v.x;
  y /= v.y;
  z /= v.z;

  return *this;
}

Vector3f& Vector3f::operator /=(const FLOAT f)
{
  x /= f;
  y /= f;
  z /= f;

  return *this;
}

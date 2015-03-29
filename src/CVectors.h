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

#ifndef SCRATCH_CVECTORS_H_INCLUDED
#define SCRATCH_CVECTORS_H_INCLUDED

#include "Common.h"

SCRATCH_NAMESPACE_BEGIN;

class SCRATCH_EXPORT Vector3f
{
public:
  FLOAT x, y, z;

public:
  Vector3f(void);
  Vector3f(FLOAT f);
  Vector3f(FLOAT fX, FLOAT fY, FLOAT fZ);
  ~Vector3f(void);

  void ClampX(const FLOAT min, const FLOAT max);
  void ClampY(const FLOAT min, const FLOAT max);
  void ClampZ(const FLOAT min, const FLOAT max);

  FLOAT Angle(const Vector3f &vOrigin);
  FLOAT Length(void);
  FLOAT Dot(const Vector3f &v2);

  void Normalize(void);

  Vector3f operator +(const Vector3f &v);
  Vector3f operator -(const Vector3f &v);
  Vector3f operator *(const Vector3f &v);
  Vector3f operator *(const FLOAT f);
  Vector3f operator /(const Vector3f &v);
  Vector3f operator /(const FLOAT f);

  BOOL operator ==(const Vector3f &v);
  BOOL operator !=(const Vector3f &v);

  Vector3f& operator +=(const Vector3f &v);
  Vector3f& operator -=(const Vector3f &v);
  Vector3f& operator *=(const Vector3f &v);
  Vector3f& operator *=(const FLOAT f);
  Vector3f& operator /=(const Vector3f &v);
  Vector3f& operator /=(const FLOAT f);
};

SCRATCH_NAMESPACE_END;

#endif

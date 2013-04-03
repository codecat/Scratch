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

#ifndef SCRATCH_CMATRIX_H_INCLUDED
#define SCRATCH_CMATRIX_H_INCLUDED 1

#ifdef USE_PRAGMAONCE
  #pragma once
#endif

#include "Common.h"
#include "CVectors.h"

SCRATCH_NAMESPACE_BEGIN;

class CMatrix
{
public:
  FLOAT _11, _12, _13, _14;
  FLOAT _21, _22, _23, _24;
  FLOAT _31, _32, _33, _34;
  FLOAT _41, _42, _43, _44;

public:
  CMatrix();
  ~CMatrix();

  void Translate(const Vector3f &v);
  void Rotate(const Vector3f &v);
  void Scale(const Vector3f &v);
};

SCRATCH_NAMESPACE_END;

#endif

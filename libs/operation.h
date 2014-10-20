/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#ifndef OPERATION_H
#define OPERATION_H

#include "qmem.h"

struct operations
{
  char  variable[MEM_VARIABLE];
  char  _operator;
  float value;
  int   line;
};

#endif

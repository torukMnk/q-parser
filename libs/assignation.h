/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#ifndef ASSIGNATION_H
#define ASSIGNATION_H

#include "qmem.h"

struct assignations
{
  char  variable[MEM_VARIABLE];
  float value;
  int   len;
  int   _operator;
};

#endif

/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#ifndef LIBQPARSER_H
#define LIBQPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sstream>
#include <iostream>

#include "qcore.h"
#include "assignation.h"
#include "operation.h"
#include "qmake.h"

class Qparser{

  struct files{
    char*   name;
    FILE*   target;
    long    size;
    char*   buffer;
    size_t  read;
    int     index;
    struct  q_files q_file;
    struct  lines line[MEM_LINE];
    struct  assignations assignation[MEM_ASSIGNATION];
    struct  operations operation[MEM_OPERATION];
  };

  files file;

  public:

  void file_load(char* file_name);
  void file_compress();
  void compile_lines();
  void compile_assignations();
  void compile_operations();
  void q_file_make();

};
#endif

/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#ifndef QPARSER_H
#define QPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sstream>
#include <iostream>

#define MEM_LINES 128
#define MEM_VARIABLES 128
#define MEM_OPERATIONS 128

class Qparser
{

  struct q_files{
    char*   buffer;
    int     elements;
    int     digits;
  };

  struct lines
  {
    char  data[MEM_VARIABLES];
    int   len;
  };

  struct asignations
  {
    char  variable[MEM_VARIABLES];
    float value;
    int   len;
    int   _operator;
  };

  struct operations
  {
    char  variable[MEM_VARIABLES];
    char  _operator;
    float value;
    int   line;
  };

  struct files{
    char*   name;
    FILE*   target;
    long    size;
    char*   buffer;
    size_t  read;
    int     index;
    struct  q_files q_file;
    struct  lines line[MEM_LINES];
    struct  asignations asignation[MEM_LINES];
    struct  operations operation[MEM_OPERATIONS];
  };

  files file;

  public:

  void file_load(char* file_name);
  void file_compress();
  void compile_lines();
  void compile_variables_assignation();
  void compile_variables_operation();
  void q_file_make();

};

#endif

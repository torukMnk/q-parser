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

  FILE *_file;
  long lSize;
  char *buffer;
  int char_count;
  size_t result;
  char *q_buffer;
  int q_count;
  int _line;
  int n_digit;

  struct lines
  {
    char line_data[MEM_VARIABLES];
    int len;
  };

  struct asignations
  {
    char variable[MEM_VARIABLES];
    float value;
    int len;
    int n_operators;
  };

  struct operations
  {
    char variable[MEM_VARIABLES];
    char _operator;
    float value;
    int line;
  };

  lines line[MEM_LINES];
  asignations asignation[MEM_LINES];
  operations operation[MEM_OPERATIONS];

  public:

  void file_read(char file_name[]);
  void file_compress();
  void compile_lines();
  void compile_variables_assignation();
  void compile_variables_operation();
  void q_file_make(char file_name[]);

};

#endif

/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include "libqparser.h"

void Qparser::compile_assignations()
{
  memset( &file.assignation, 0, sizeof(file.assignation) );
  int qchar;
  int index;
  qchar = 0;

  for(index=0; index < file.index; index++)
  {
    while(file.line[index].data[qchar] != '=')
    {
      file.assignation[index].variable[qchar] = file.line[index].data[qchar];
      qchar++;
    };

    file.assignation[index].len = strlen(file.assignation[index].variable);
    qchar = 0;
  }
}

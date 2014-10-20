/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include "libqparser.h"

void Qparser::compile_lines()
{
  memset( &file.line, 0, sizeof(file.line) );
  int qchar;
  int fchar;
  fchar = 0;

  for(qchar = 0; qchar < file.q_file.elements; qchar++)
  {
    file.line[file.index].data[fchar] = file.q_file.buffer[qchar];
    fchar++;
    if( file.q_file.buffer[qchar] == ';' )
    {
      file.line[file.index].len = strlen(file.line[file.index].data);
      file.index++;
      fchar = 0;
    }
  }
  free(file.q_file.buffer);
}

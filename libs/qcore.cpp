/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include "libqparser.h"

void Qparser::file_load(char* file_name)
{
  file.name = file_name;
  file.target = fopen(file.name,"rb");
  if (file.target==NULL) {fputs ("No such file\n",stderr); exit (1);}
  fseek(file.target,0,SEEK_END);
  file.size = ftell(file.target);
  rewind(file.target);
  file.buffer = (char*)malloc(sizeof(char)*file.size);
  file.read = fread(file.buffer,1,file.size,file.target);
  fclose (file.target);

  file.q_file.elements = 0;
  file.q_file.buffer = (char*)malloc(sizeof(char)*file.size);
  file.index = 0;
  file.q_file.digits = 0;
}

void Qparser::file_compress()
{
  int position;
  for(position = 0;position < file.size;position++)
  {
    if(file.buffer[position] != ' ' )
    {
      file.q_file.buffer[file.q_file.elements] = file.buffer[position];
      file.q_file.elements +=1;
    }
  }
  free(file.buffer);
}

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

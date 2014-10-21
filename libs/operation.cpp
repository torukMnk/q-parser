/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include "libqparser.h"

void Qparser::compile_operations()
{
  memset( &file.operation, 0, sizeof(file.operation) );
  int iline;
  int len;
  int ichar;
  int next;
  int qchar;
  int assignation;

  len = 0;
  next = 0;
  assignation = 0;

  for(iline=0; iline < file.index; iline++)
  {
    qchar = file.assignation[iline].len+1;
    len = file.line[iline].len;

    for(ichar=0; ichar < len; ichar++)
    {
      if (isdigit(file.line[iline].data[qchar]))
      {
        file.operation[file.q_file.digits].variable[next] = file.line[iline].data[qchar];
        file.operation[file.q_file.digits].line = iline;
        next +=1;
        qchar+=1;
      }
      else if(isalpha(file.line[iline].data[qchar]))
      {
        file.operation[file.q_file.digits].variable[next] = file.line[iline].data[qchar];
        file.operation[file.q_file.digits].line = iline;
        next +=1;
        qchar+=1;
      }

      else
      {
        if(file.line[iline].data[qchar] != ';')
        {
          file.operation[file.q_file.digits+1]._operator = file.line[iline].data[qchar];
        }
        file.q_file.digits +=1;
        next = 0;
        qchar +=1;
      }
      if(qchar == len) ichar = len;
    }
  }

  //ASCII TO INTEGER
  for(iline = 0; iline < file.q_file.digits; iline++)
  {
    file.operation[iline].value = atoi(file.operation[iline].variable);
  }

  //Operaciones Algebraicas Basicas(Lineal)
  float total;
  int index_operator;
  total = 0;
  index_operator = 0;
  for(iline = 0; iline < file.index+1; iline++)
  {
    for(ichar = 0; ichar < file.q_file.digits; ichar++)
    {
      if(file.operation[ichar].line == iline)
      {
        if(isalpha(file.operation[ichar].variable[0]))
        {
          if(strcmp(file.operation[ichar].variable,file.assignation[ichar].variable))
          {
            file.operation[ichar].value = file.assignation[assignation].value;
            assignation += 1;
          }
        }

        index_operator +=1;
        file.assignation[iline]._operator = index_operator;
        if(file.operation[ichar]._operator == '\0')
        {
          total += file.operation[ichar].value;
          file.assignation[iline].value = total;
        }
        if(file.operation[ichar]._operator == '+')
        {

          total += file.operation[ichar].value;
          file.assignation[iline].value = total;
        }
        if(file.operation[ichar]._operator == '-')
        {
          total -= file.operation[ichar].value;
          file.assignation[iline].value = total;
        }
        if(file.operation[ichar]._operator == '*')
        {
          total *= file.operation[ichar].value;
          file.assignation[iline].value = total;
        }
        if(file.operation[ichar]._operator == '/')
        {
          total /= file.operation[ichar].value;
          file.assignation[iline].value = total;
        }


      }
      else
      {
        total = 0;
        index_operator = 0;
      }
    }
  }

}

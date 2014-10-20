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
  int index;
  int len;
  int _char;
  int _digit;
  int qchar;
  int assignation;

  len = 0;
  _digit = 0;
  assignation = 0;

  for(index=0;index < file.index; index++)
  {
    qchar = file.assignation[index].len+1;
    len = file.line[index].len;

    for(_char=0; _char < len; _char++)
    {
      if (isdigit(file.line[index].data[qchar]))
      {
        file.operation[file.q_file.digits].variable[_digit] = file.line[index].data[qchar];
        file.operation[file.q_file.digits].line = index;
        _digit +=1;
        qchar+=1;
      }
      else if(isalpha(file.line[index].data[qchar]))
      {
        file.operation[file.q_file.digits].variable[_digit] = file.line[index].data[qchar];
        file.operation[file.q_file.digits].line = index;
        _digit +=1;
        qchar+=1;
      }

      else
      {
        if(file.line[index].data[qchar] != ';')
        {
          file.operation[file.q_file.digits+1]._operator = file.line[index].data[qchar];
        }
        file.q_file.digits +=1;
        _digit = 0;
        qchar +=1;
      }
      if(qchar == len) _char = len;
    }
  }

  //ASCII TO INTEGER
  for(index = 0; index < file.q_file.digits; index++)
  {
    file.operation[index].value = atoi(file.operation[index].variable);
  }

  //Operaciones Algebraicas Basicas(Lineal)
  float total;
  int index_operator;
  total = 0;
  index_operator = 0;
  for(index = 0; index < file.index+1; index++)
  {
    for(_char = 0; _char < file.q_file.digits; _char++)
    {
      if(file.operation[_char].line == index)
      {
        if(isalpha(file.operation[_char].variable[0]))
        {
          if(strcmp(file.operation[_char].variable,file.assignation[_char].variable))
          {
            file.operation[_char].value = file.assignation[assignation].value;
            assignation += 1;
          }
        }

        index_operator +=1;
        file.assignation[index]._operator = index_operator;
        if(file.operation[_char]._operator == '\0')
        {
          total += file.operation[_char].value;
          file.assignation[index].value = total;
        }
        if(file.operation[_char]._operator == '+')
        {

          total += file.operation[_char].value;
          file.assignation[index].value = total;
        }
        if(file.operation[_char]._operator == '-')
        {
          total -= file.operation[_char].value;
          file.assignation[index].value = total;
        }
        if(file.operation[_char]._operator == '*')
        {
          total *= file.operation[_char].value;
          file.assignation[index].value = total;
        }
        if(file.operation[_char]._operator == '/')
        {
          total /= file.operation[_char].value;
          file.assignation[index].value = total;
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

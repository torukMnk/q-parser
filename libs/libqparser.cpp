/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include "libqparser.h"
using namespace std;

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
    fchar +=1;
    if( file.q_file.buffer[qchar] == ';' )
    {
      file.line[file.index].len = strlen(file.line[file.index].data);
      file.index +=1;
      fchar = 0;
    }
  }
  free(file.q_file.buffer);
}

void Qparser::compile_variables_assignation()
{
  memset( &file.asignation, 0, sizeof(file.asignation) );
  int qchar;
  int index;
  qchar = 0;
  for(index=0;index < file.index;index++)
  {
    while(file.line[index].data[qchar] != '=')
    {
      file.asignation[index].variable[qchar] = file.line[index].data[qchar];
      qchar +=1;
    };
    file.asignation[index].len = strlen(file.asignation[index].variable);
    qchar = 0;
  }
}

void Qparser::compile_variables_operation()
{
  memset( &file.operation, 0, sizeof(file.operation) );
  int index;
  int len;
  int _char;
  int _digit;
  int qchar;
  int asignation;

  len = 0;
  _digit = 0;
  asignation = 0;

  for(index=0;index < file.index; index++)
  {
    qchar = file.asignation[index].len+1;
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
          if(strcmp(file.operation[_char].variable,file.asignation[_char].variable))
          {
            file.operation[_char].value = file.asignation[asignation].value;
            asignation += 1;
          }
        }

        index_operator +=1;
        file.asignation[index]._operator = index_operator;
        if(file.operation[_char]._operator == '\0')
        {
          total += file.operation[_char].value;
          file.asignation[index].value = total;
        }
        if(file.operation[_char]._operator == '+')
        {

          total += file.operation[_char].value;
          file.asignation[index].value = total;
        }
        if(file.operation[_char]._operator == '-')
        {
          total -= file.operation[_char].value;
          file.asignation[index].value = total;
        }
        if(file.operation[_char]._operator == '*')
        {
          total *= file.operation[_char].value;
          file.asignation[index].value = total;
        }
        if(file.operation[_char]._operator == '/')
        {
          total /= file.operation[_char].value;
          file.asignation[index].value = total;
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

void Qparser::q_file_make()
{
  char q_file[16];
  strcpy(q_file,"q-");
  strcat(q_file,file.name);
  file.target = fopen (q_file,"w");
  int j;
  cout<<"========================================================"<<endl;
  cout<<">>Content"<<endl;
  cout<<"========================================================"<<endl;
  stringstream lineas;
  for(j = 0;j < file.index;j++)
  {
    lineas<<file.line[j].data;
  }
  lineas<<"\n>>Compiled Lines: "<<file.index<<"\n";
  string data_l = lineas.str();
  fputs(data_l.c_str(),file.target);
  cout<<data_l<<endl;

  cout<<"========================================================"<<endl;
  cout<<">>Variables"<<endl;
  cout<<"========================================================"<<endl;
  stringstream variables;
  for(j = 0;j < file.index;j++)
  {
    variables<<file.asignation[j].variable;
  }
  variables<<"\n>>Asignations: "<<file.index<<"\n";
  string data_v = variables.str();
  fputs(data_v.c_str(),file.target);
  cout<<data_v<<endl;

  cout<<"========================================================"<<endl;
  cout<<">>Constants"<<endl;
  cout<<"========================================================"<<endl;
  for(j = 0; j < file.q_file.digits-1; j++)
  {
    cout<<"Line["<<file.operation[j].line+1<<"] >>"<<file.operation[j].value<<endl;
  }

  cout<<"========================================================"<<endl;
  cout<<">>Operators"<<endl;
  cout<<"========================================================"<<endl;
  for(j = 0; j < file.q_file.digits; j++)
  {
    if(file.operation[j]._operator == '+')
    {
      cout<<"Line: ["<<file.operation[j].line+1<<"] ("<<file.operation[j]._operator<<")SUMA"<<endl;
    }
    if(file.operation[j]._operator == '-')
    {
      cout<<"Line: ["<<file.operation[j].line+1<<"] ("<<file.operation[j]._operator<<")RESTA"<<endl;
    }
    if(file.operation[j]._operator == '*')
    {
      cout<<"Line: ["<<file.operation[j].line+1<<"] ("<<file.operation[j]._operator<<")MULTIPLICACION"<<endl;
    }
    if(file.operation[j]._operator == '/')
    {
      cout<<"Line: ["<<file.operation[j].line+1<<"] ("<<file.operation[j]._operator<<")DIVICION"<<endl;
    }

  }

  cout<<"========================================================"<<endl;
  cout<<">>Result"<<endl;
  cout<<"========================================================"<<endl;
  stringstream resultados;
  for(j = 0;j < file.index;j++)
  {
    resultados<<file.asignation[j].variable<<"="<<file.asignation[j].value;
  }
  resultados<<"\n>>Result"<<"\n";
  string data_r = resultados.str();
  fputs(data_r.c_str(),file.target);
  cout<<data_r<<endl;
  fclose (file.target);
}


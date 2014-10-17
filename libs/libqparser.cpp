/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include "libqparser.h"
using namespace std;

void Qparser::file_read(char file_name[])
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
}

void Qparser::file_compress()
{
  int position;
  file.q_file.elements = 0;
  file.q_file.buffer = (char*)malloc(sizeof(char)*file.size);
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
  int _char;
  int _data;
  file.index = 0;
  _data = 0;

  for(_char = 0; _char < file.q_file.elements; _char++)
  {
    file.line[file.index].data[_data] = file.q_file.buffer[_char];
    _data +=1;
    if( file.q_file.buffer[_char] == ';' )
    {
      file.line[file.index].len = strlen(file.line[file.index].data);
      file.index +=1;
      _data = 0;
    }
  }
  free(file.q_file.buffer);
}

void Qparser::compile_variables_assignation()
{
  memset( &file.asignation, 0, sizeof(file.asignation) );
  int _char;
  int i;
  _char = 0;
  for(i=0;i < file.index;i++)
  {
    while(file.line[i].data[_char] != '=')
    {
      file.asignation[i].variable[_char] = file.line[i].data[_char];
      _char +=1;
    };
    file.asignation[i].len = strlen(file.asignation[i].variable);
    _char = 0;
  }
}

void Qparser::compile_variables_operation()
{
  memset( &file.operation, 0, sizeof(file.operation) );
  int i;                  //Numero de Linea
  int len;                //Longitud de linea
  int k;                  //Lector de caracteres en la linea
  int _digit;             //Posicion de nuevo valor en la linea digit
  int _char;
  int count_as;           //Variables asignacion indirectas

  len = 0;
  file.q_file.digits = 0;
  _digit = 0;
  count_as = 0;

  for(i=0;i < file.index; i++)
  {
    _char = file.asignation[i].len+1;
    len = file.line[i].len;

    for(k=0; k < len; k++)
    {
      if (isdigit(file.line[i].data[_char]))
      {
        file.operation[file.q_file.digits].variable[_digit] = file.line[i].data[_char];
        file.operation[file.q_file.digits].line = i;
        _digit +=1;
        _char+=1;
      }
      else if(isalpha(file.line[i].data[_char]))
      {
        file.operation[file.q_file.digits].variable[_digit] = file.line[i].data[_char];
        file.operation[file.q_file.digits].line = i;
        _digit +=1;
        _char+=1;
      }

      else
      {
        if(file.line[i].data[_char] != ';')
        {
          file.operation[file.q_file.digits+1]._operator = file.line[i].data[_char];
        }
        file.q_file.digits +=1;
        _digit = 0;
        _char +=1;
      }
      if(_char == len) k = len;
    }
  }

  //ASCII TO INTEGER
  for(i = 0; i < file.q_file.digits; i++)
  {
    file.operation[i].value = atoi(file.operation[i].variable);
  }

  //Operaciones Algebraicas Basicas(Lineal)
  float total;
  int n_operator;
  total = 0;
  n_operator = 0;
  for(i = 0; i < file.index+1; i++)
  {
    for(k = 0; k < file.q_file.digits; k++)
    {
      if(file.operation[k].line == i)
      {
        if(isalpha(file.operation[k].variable[0]))
        {
          if(strcmp(file.operation[k].variable,file.asignation[k].variable))
          {
            file.operation[k].value = file.asignation[count_as].value;
            count_as += 1;
          }
        }

        n_operator +=1;
        file.asignation[i].n_operators = n_operator;
        if(file.operation[k]._operator == '\0')
        {
          total += file.operation[k].value;
          file.asignation[i].value = total;
        }
        if(file.operation[k]._operator == '+')
        {

          total += file.operation[k].value;
          file.asignation[i].value = total;
        }
        if(file.operation[k]._operator == '-')
        {
          total -= file.operation[k].value;
          file.asignation[i].value = total;
        }
        if(file.operation[k]._operator == '*')
        {
          total *= file.operation[k].value;
          file.asignation[i].value = total;
        }
        if(file.operation[k]._operator == '/')
        {
          total /= file.operation[k].value;
          file.asignation[i].value = total;
        }


      }
      else
      {
        total = 0;
        n_operator = 0;
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
  cout<<file.q_file.digits-1<<endl;
  fclose (file.target);
}


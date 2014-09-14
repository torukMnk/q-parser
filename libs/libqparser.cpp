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
  _file = fopen(file_name,"rb");
  if (_file==NULL) {fputs ("File error",stderr); exit (1);}
  fseek(_file,0,SEEK_END);
  lSize = ftell(_file);
  rewind(_file);
  buffer = (char*)malloc(sizeof(char)*lSize);
  result = fread(buffer,1,lSize,_file);
  fclose (_file);
}

void Qparser::file_compress()
{
  q_count = 0;
  q_buffer = (char*)malloc(sizeof(char)*lSize);
  for(char_count = 0;char_count < lSize;char_count++)
  {
    if(buffer[char_count] != ' ' )
    {
      q_buffer[q_count] = buffer[char_count];
      q_count +=1;
    }
  }
  free(buffer);
}

void Qparser::compile_lines()
{
  memset( &line, 0, sizeof(line) );
  int _char;
  int _data;
  _line = 0;
  _data = 0;

  for(_char = 0; _char < q_count; _char++)
  {
    line[_line].line_data[_data] = q_buffer[_char];
    _data +=1;
    if( q_buffer[_char] == ';' )
    {
      line[_line].len = strlen(line[_line].line_data);
      _line +=1;
      _data = 0;
    }
  }
  free(q_buffer);
}

void Qparser::compile_variables_assignation()
{
  memset( &asignation, 0, sizeof(asignation) );
  int _char;
  int i;
  _char = 0;
  for(i=0;i < _line;i++)
  {
    while(line[i].line_data[_char] != '=')
    {
      asignation[i].variable[_char] = line[i].line_data[_char];
      _char +=1;
    };
    asignation[i].len = strlen(asignation[i].variable);
    _char = 0;
  }
}

void Qparser::compile_variables_operation()
{
  memset( &operation, 0, sizeof(operation) );
  int i;                  //Numero de Linea
  int len;                //Longitud de linea
  int k;                  //Lector de caracteres en la linea
  int _digit;             //Posicion de nuevo valor en la linea digit
  int _char;
  int count_as;           //Variables asignacion indirectas

  len = 0;
  n_digit = 0;
  _digit = 0;
  count_as = 0;

  for(i=0;i < _line; i++)
  {
    _char = asignation[i].len+1;
    len = line[i].len;

    for(k=0; k < len; k++)
    {
      if (isdigit(line[i].line_data[_char]))
      {
        operation[n_digit].variable[_digit] = line[i].line_data[_char];
        operation[n_digit].line = i;
        _digit +=1;
        _char+=1;
      }
      else if(isalpha(line[i].line_data[_char]))
      {
        operation[n_digit].variable[_digit] = line[i].line_data[_char];
        operation[n_digit].line = i;
        _digit +=1;
        _char+=1;
      }

      else
      {
        if(line[i].line_data[_char] != ';')
        {
          operation[n_digit+1]._operator = line[i].line_data[_char];
        }
        n_digit +=1;
        _digit = 0;
        _char +=1;
      }
      if(_char == len) k = len;
    }
  }

  //ASCII TO INTEGER
  for(i = 0; i < n_digit; i++)
  {
    operation[i].value = atoi(operation[i].variable);
  }

  //Operaciones Algebraicas Basicas(Lineal)
  float total;
  int n_operator;
  total = 0;
  n_operator = 0;
  for(i = 0; i < _line+1; i++)
  {
    for(k = 0; k < n_digit; k++)
    {
      if(operation[k].line == i)
      {
        if(isalpha(operation[k].variable[0]))
        {
          if(strcmp(operation[k].variable,asignation[k].variable))
          {
            operation[k].value = asignation[count_as].value;
            count_as += 1;
          }
        }

        n_operator +=1;
        asignation[i].n_operators = n_operator;
        if(operation[k]._operator == '\0')
        {
          total += operation[k].value;
          asignation[i].value = total;
        }
        if(operation[k]._operator == '+')
        {

          total += operation[k].value;
          asignation[i].value = total;
        }
        if(operation[k]._operator == '-')
        {
          total -= operation[k].value;
          asignation[i].value = total;
        }
        if(operation[k]._operator == '*')
        {
          total *= operation[k].value;
          asignation[i].value = total;
        }
        if(operation[k]._operator == '/')
        {
          total /= operation[k].value;
          asignation[i].value = total;
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

void Qparser::q_file_make(char file_name[])
{
  char f_name[16];
  strcpy(f_name,"q-");
  strcat(f_name,file_name);
  _file = fopen (f_name,"w");
  int j;
  cout<<"========================================================"<<endl;
  cout<<">>Contenido"<<endl;
  cout<<"========================================================"<<endl;
  stringstream lineas;
  for(j = 0;j < _line;j++)
  {
    lineas<<line[j].line_data;
  }
  lineas<<"\n>>Lineas compiladas: "<<_line<<"\n";
  string data_l = lineas.str();
  fputs(data_l.c_str(),_file);
  cout<<data_l<<endl;

  cout<<"========================================================"<<endl;
  cout<<">>Variables"<<endl;
  cout<<"========================================================"<<endl;
  stringstream variables;
  for(j = 0;j < _line;j++)
  {
    variables<<asignation[j].variable;
  }
  variables<<"\n>>Asignacion: "<<_line<<"\n";
  string data_v = variables.str();
  fputs(data_v.c_str(),_file);
  cout<<data_v<<endl;

  cout<<"========================================================"<<endl;
  cout<<">>Constantes"<<endl;
  cout<<"========================================================"<<endl;
  for(j = 0; j < n_digit-1; j++)
  {
    cout<<"Linea["<<operation[j].line+1<<"] >>"<<operation[j].value<<endl;
  }

  cout<<"========================================================"<<endl;
  cout<<">>Operadores"<<endl;
  cout<<"========================================================"<<endl;
  for(j = 0; j < n_digit; j++)
  {
    if(operation[j]._operator == '+')
    {
      cout<<"Linea: ["<<operation[j].line+1<<"] ("<<operation[j]._operator<<")SUMA"<<endl;
    }
    if(operation[j]._operator == '-')
    {
      cout<<"Linea: ["<<operation[j].line+1<<"] ("<<operation[j]._operator<<")RESTA"<<endl;
    }
    if(operation[j]._operator == '*')
    {
      cout<<"Linea: ["<<operation[j].line+1<<"] ("<<operation[j]._operator<<")MULTIPLICACION"<<endl;
    }
    if(operation[j]._operator == '/')
    {
      cout<<"Linea: ["<<operation[j].line+1<<"] ("<<operation[j]._operator<<")DIVICION"<<endl;
    }

  }

  cout<<"========================================================"<<endl;
  cout<<">>Resultados"<<endl;
  cout<<"========================================================"<<endl;
  stringstream resultados;
  for(j = 0;j < _line;j++)
  {
    resultados<<asignation[j].variable<<"="<<asignation[j].value;
  }
  resultados<<"\n>>Resultados"<<"\n";
  string data_r = resultados.str();
  fputs(data_r.c_str(),_file);
  cout<<data_r<<endl;
  fclose (_file);
}


/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include "libqparser.h"
using namespace std;

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
    variables<<file.assignation[j].variable;
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
    resultados<<file.assignation[j].variable<<"="<<file.assignation[j].value;
  }
  resultados<<"\n>>Result"<<"\n";
  string data_r = resultados.str();
  fputs(data_r.c_str(),file.target);
  cout<<data_r<<endl;
  fclose (file.target);
}


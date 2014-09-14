/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include <libqparser.h>
using namespace std;

int main(void)
{
  Qparser com;
  char option;
  char name[16];

  do{
    system("clear");      //Linux
    cout<<":: Q Compiler ::"<<endl;
    cout<<"Nombre del archivo: ";
    cin>>name;
    cout<<endl;
    com.file_read(name);
    com.file_compress();
    com.compile_lines();
    com.compile_variables_assignation();
    com.compile_variables_operation();
    com.q_file_make(name);

    cout<<"Desea compilar otro archivo: (Y/N): ";
    cin>>option;
    option = toupper(option);

  }while(option != 'N');
}

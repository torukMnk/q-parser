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
    system("clear");
    cout<<":: Q Compiler ::"<<endl;
    cout<<"Insert name file: ";
    cin>>name;
    cout<<endl;
    com.file_read(name);
    com.file_compress();
    com.compile_lines();
    com.compile_variables_assignation();
    com.compile_variables_operation();
    com.q_file_make();

    cout<<"Do you want compile another file: (Y/N): ";
    cin>>option;
    option = toupper(option);

  }while(option != 'N');
}

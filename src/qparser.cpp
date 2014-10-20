/**
 * UDC 2013
 * Developer: Guillermo Quezada de Pedro
 * Semester: 6 Grupo "F"
 * Professor: M.C. Benjamin Iglesias Cortes
 *
 * */
#include <libqparser.h>
using namespace std;

int main(int argc,char* argv[])
{

  system("clear");
  cout<<":: Q Compiler ::"<<endl;
  Qparser com;

  if(argc == 2){
    com.file_load(argv[1]);
    com.file_compress();
    com.compile_lines();
    com.compile_assignations();
    com.compile_operations();
    com.q_file_make();
  }
  else
    cout<<"No such file"<<endl;

  return 0;
}

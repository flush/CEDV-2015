#include "records.h"


int main (int argc, char * argv [])
{
  records r;
  string  name;
  int  points;
  int result;

  result = r.loadFile ("/tmp/input");
  cout << "RESULT " << result << endl;
  r.print();
  r.add_record ("test", 1000);
  r.add_record ("test2", 2000);
  r.add_record ("test3", 3);
  r.add_record ("testdup", 1000);
  r.print();
  r.saveFile();
  
  result = r.getNext(name,points,true);
  while (result == 0)
  {
    cout << name << ":" << points<<endl;
    result = r.getNext(name,points);
  }
    

  return 0;
}


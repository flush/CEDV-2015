#ifndef __RECORS__H
#define __RECORS__H

#include <iostream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define SEPARATOR "|"
#define DEFAULT_RECORDS_FILE "/tmp/input"

using namespace std;

typedef struct records_entry
{
  string name;
  int points;
  records_entry(string n,int p){name=n;points=p;};
} records_entry;

class records
{
  private:
    string path;
    vector <records_entry> records_vector;
    static bool sort_records(records_entry pre, records_entry next);
  public:
    records ();
    int loadFile(string path);
    int saveFile (string * save_path=NULL);
    const vector <records_entry> getList (int amount =10);
    int add_record (string name, int points);
    void print ();
    int getNext (string & name,int & points, bool begin=false);
};

#endif

/**
 * @file   common.cpp
 * @Author jalcoleam@gmail.com
 * @date   November, 2015
 * @brief  
 *
 * Detailed
 */
#include "common.h"

char * print_disp_result (disp_result disp)
{
  static char * result [4]={(char*)"HIT",(char*)"SUNK",(char*)"WATER",(char*)"DEFEAT"};
  return result [disp];
}

int random (int max, int min)
{
  static int first = 0;
  int v = -1;
  if (max > 7) max=7;
  if (min < 0) min=0;

  if (first == 0)
  {
    srand (time(NULL));
    first = 1;
  }
  while (v < min) v = rand()%(max+1);
  return v;
}


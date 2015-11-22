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
  static char * result [4]={(char*)"TOCADO",(char*)"HUNDIDO",(char*)"AGUA",(char*)"DERROTA"};
  return result [disp];
}


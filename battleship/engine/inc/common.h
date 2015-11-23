/**
 * @file   common.h
 * @Author jalcoleam@gmail.com
 * @date   November, 2015
 * @brief 
 *
 * Detailed 
 */

#ifndef __COMMON__
#define __COMMON__


#define MAX_TAM_BARCO 5
#define MAX_X 8
#define MAX_Y 8


typedef enum orientacion { horizontal, vertical} orientacion;
typedef enum disp_result {tocado, hundido, agua, derrota} disp_result;

/**
 * helper function which prints the disp_result info received as a parameter.
 * @param disp shoot result to be translated
 * @return shoot result translation
 */
char * print_disp_result (disp_result disp);


#endif

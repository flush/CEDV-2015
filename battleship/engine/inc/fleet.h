/**
 * @file   fleet.h
 * @Author jalcoleam@gmail.com
 * @date   November, 2015
 * @brief  
 *
 * Detailed 
 */

#ifndef __FLOTA__
#define __FLOTA__

#include <iostream>
#include "common.h"
#include "ship.h"
#include <vector>

using namespace std;

class fleet
{
  private:
char play [MAX_X][MAX_Y];
/*
char play [MAX_X][MAX_Y]={ \
' ',' ',' ',' ',' ',' ',' ',' ', \
' ',' ',' ',' ',' ',' ',' ',' ', \
' ',' ',' ',' ',' ',' ',' ',' ', \
' ',' ',' ',' ',' ',' ',' ',' ', \
' ',' ',' ',' ',' ',' ',' ',' ', \
' ',' ',' ',' ',' ',' ',' ',' ', \
' ',' ',' ',' ',' ',' ',' ',' ', \
' ',' ',' ',' ',' ',' ',' ',' ', \
};
*/

  std::vector<ship *> barcos;
  public:
/**
 * Default constructor
 */
  fleet ();

/**
 * Add a new ship
 * @param x starting x position
 * @param y starting y position
 * @param o orientation (^ or >)
 * @param l ship legth 
 */
  int new_ship (int x, int y, orientacion o, int l);

/**
 * prints all x,y positions of the ship
 */
  void print ();

/**
 * new shot to this ship
 * @param x shoot x coordinateOB
 * @param y shoot y coordinate
 * @return disp_result (hit, sunk, water or fleet destroyed
*/  
  disp_result disparo (int x, int y);

/**
 * test if a x,y position is already shooted before
 * @param x x coordinate to check
 * @param y y coordinate to check
 * @return true if it is used or false if it is available to be shooted
 */
  bool used (int x,int y); 
};

#endif
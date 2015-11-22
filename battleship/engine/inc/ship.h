/**
 * @file   ship.h
 * @Author jalcoleam@gmail.com
 * @date   November, 2015
 * @brief  
 *
 * Detailed 
 */

#ifndef __BARCO__
#define __BARCO__

#include <iostream>
#include "common.h"

using namespace std;

class ship 
{
  private: 
    int _x_init;
    int _y_init;
    orientacion _orient;
    int _length;
    int _id;
    int _x_ro [MAX_TAM_BARCO];
    int _y_ro [MAX_TAM_BARCO];
    int _x [MAX_TAM_BARCO];
    int _y [MAX_TAM_BARCO];
    disp_result _estado;
    void iniciar_matriz();
  public:

/**
 * ship constructor
 * @param x first x position of the ship
 * @param y first y position of the ship
 * @param orient ship orientation (^ or <)
 * @param length ship length
 * @param id , optional parameter which sets the ship id
 */
   ship (int x, int y, orientacion orient, int length, int id =0);

/**
 * sets a ship id
 * @param id id to set
 */ 
   void id (int id);

/**
 * returns the ship id
 * @return ship id
 */
   int  id ();

   //void x (int x);
/**
 * returns the first x position
 * @return first x positon
 */ 
   int  x ();

   //void y (int y);
/**
 * returns the first y position
 * @return first y position
 */ 
   int  y ();

/**
 * check the ship status
 * @return disp_result, ship status, (hit, shunk or free)
 */
   disp_result estado();

/**
 * new shoot
 * @param x x shoot element
 * @param y y shoot element
 * @return (hit, sunk or water)
 */
   disp_result disparo (int x, int y);

/**
 * gets the ship orientation
 * @return ship orientation (^ or >)
 */
   orientacion orient();

//   void orient( orientacion o);

/**
 * returns the ship length
 * @return ship length
 */
   int length();
  // void length (int l);

/**
 * returns all the ship x,y positions
 * @param matrix, buffer where the x,y matrix well be returned
 * @return ship length
 */
   int get_matrix (char * matriz);

/** 
 *prints all x,y ship positions
 */
   void print ();
};

#endif

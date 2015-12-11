#ifndef _SHIP_OGRE_WRAPPER_H
#define _SHIP_OGRE_WRAPPER_H
#include <Ogre.h>
#include "ship.h"
class ShipOgreWrapper {
 private:
  int _id;
  Ogre::Vector3 *_originalPosition;
  //ship* _ship;

 public:
  ShipOgreWrapper(int id,Ogre::Vector3* position);
  ~ShipOgreWrapper();
  void paintShip(Ogre::SceneManager * _sceneManager,
                             Ogre::SceneNode * _parentNode,                             
                              Ogre::Vector3* position);
  
};





#endif

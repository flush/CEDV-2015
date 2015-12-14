#ifndef _SHIP_OGRE_WRAPPER_H
#define _SHIP_OGRE_WRAPPER_H
#include <Ogre.h>
#include "ship.h"

class ShipOgreWrapper {
 private:
  const float sizes[4] = {0.5, 0.7, 0.85, 1.05};
  int _id;
  Ogre::Vector3 *_originalPosition;
  Ogre::SceneNode *_node;
  ship* _ship;

 public:
  ShipOgreWrapper(int id,Ogre::Vector3* position, int size);
  ~ShipOgreWrapper();
  void setShip(ship* ship);
  int getId();
  ship* getShip();
  void setShipBoardPosition(int x, int y);
  void setShipPosition(const Ogre::Vector3 &newPos);
  bool isPlaced();
  void rotateShip();
  void paintShip(Ogre::SceneManager * _sceneManager,
                             Ogre::SceneNode * _parentNode,                             
                              Ogre::Vector3* position);
};





#endif

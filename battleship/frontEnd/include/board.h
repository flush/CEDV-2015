#ifndef _BOARD_H
#define _BOARD_H
#include <Ogre.h>
#include <vector>
#include "shipOgreWrapper.h"

class Board {

 private:
  char* _id;
  std::vector<ShipOgreWrapper> ships;
  Ogre::Vector3* firstBoxpos;
  void placeBoxes(char* idBoard, Ogre::Node* boardNode,
                  Ogre::SceneManager* _sceneManager);



 public:
  Board(char* id);
  ~Board();
  void paintBoard(Ogre::SceneManager * _sceneManager,
                             Ogre::SceneNode * _parentNode,                             
                              Ogre::Vector3* position);
  void addShip(ShipOgreWrapper &ship );


};
#endif

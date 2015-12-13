#ifndef _BOARD_H
#define _BOARD_H
#include <Ogre.h>
#include <vector>
#include "shipOgreWrapper.h"
#include "fleet.h"

class Board {

 private:
  char* _id;
  std::vector<ShipOgreWrapper> ships;
  Ogre::Vector3* firstBoxpos;
  fleet *fleetBoard;
  void placeBoxes(char* idBoard, Ogre::Node* boardNode,
                  Ogre::SceneManager* _sceneManager);



 public:
  ShipOgreWrapper* getShip(Ogre::Node* node);
  ShipOgreWrapper* getShip(int id);
  explicit Board(char* id);
  ~Board();
  void paintBoard(Ogre::SceneManager * _sceneManager,
                             Ogre::SceneNode * _parentNode,                             
                              Ogre::Vector3* position);
  void addShip(ShipOgreWrapper *ogreShip );


};
#endif

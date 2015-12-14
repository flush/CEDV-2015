#ifndef _BOARD_H
#define _BOARD_H
#include <Ogre.h>
#include <vector>
#include "shipOgreWrapper.h"
#include "fleet.h"

#define FLEET_BOARD 1
#define SHOOT_BOARD 2
class Board {

 private:
  char* _id;
  int _type;
  std::vector<ShipOgreWrapper*> ships;
  Ogre::Vector3* firstBoxpos;
  fleet *fleetBoard;
  void placeBoxes(char* idBoard, Ogre::Node* boardNode,
                  Ogre::SceneManager* _sceneManager);
  void allocate_random_ships();



 public:
  ShipOgreWrapper* getShip(Ogre::Node* node);
  ShipOgreWrapper* getShip(int id);
  Board(char* id, int type);
  ~Board();
  void paintBoard(Ogre::SceneManager * _sceneManager,
                             Ogre::SceneNode * _parentNode,                             
                              Ogre::Vector3* position);
  void addShip(ShipOgreWrapper *ogreShip);
  void setShipBoardPosition(int x, int y, int idShip);
  disp_result shoot(int x, int y, Ogre::SceneNode* node);
  bool areAllShipsPlaced();
  disp_result inteligent_cpu_play ();
  int getPoints();
  
};
#endif

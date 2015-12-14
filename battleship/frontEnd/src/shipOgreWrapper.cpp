// Copyright [2015] <Alfredo Arteaga>
#include "shipOgreWrapper.h"
#include "const.h"
#include "ship.h"
#include <string>

ShipOgreWrapper::ShipOgreWrapper(int id, Ogre::Vector3* position,int size):_id(id),_originalPosition(position) {
  this->_ship = new ship (-1, -1, horizontal, size, id);
  this->_node = NULL;
}
void ShipOgreWrapper::paintShip(Ogre::SceneManager * _sceneManager,
                                Ogre::SceneNode * _parentNode,                             
                                Ogre::Vector3* position) {

  std::stringstream ss;
  ss << _id;
  Ogre::SceneNode* node = _sceneManager->createSceneNode(ss.str());

  Ogre::Entity* ship = _sceneManager->createEntity("ship.mesh");

  const Ogre::Vector3 &scaleShip = Ogre::Vector3(this->sizes[this->_ship->length()-1],
                                                 0.8, 1);
  ship->setQueryFlags(SHIP);
  node->attachObject(ship);
  node->scale(scaleShip);
  node->translate(*(this->_originalPosition),
                  Ogre::Node::TS_WORLD);
  node->scale(scaleShip);
  _parentNode->addChild(node);
  this->_node = node;
}

/*
 *Set Ship boards Game Coords position
 */
void ShipOgreWrapper::setShipBoardPosition(int x, int y) {
  this->_ship->setPosition(x, y);
}

/*
 *Set Ship Node Position
 */
void ShipOgreWrapper::setShipPosition(const Ogre::Vector3 &newPos) {
  this->_node->setPosition(newPos);
}

/*void ShipOgreWrapper::changeOrientation(){

  }*/
                          
void ShipOgreWrapper::setShip(ship* ship) {
  if (this->_ship != NULL) {
    delete this->_ship;
  }
  this->_ship = ship;
}

ship* ShipOgreWrapper::getShip() {
  return this->_ship;
}


ShipOgreWrapper::~ShipOgreWrapper() {
  delete this->_originalPosition;
  delete this->_ship;
}
int ShipOgreWrapper::getId() {
  return this->_id;
}

bool ShipOgreWrapper::isPlaced() {
  return this->_ship->x() != -1;
}


void ShipOgreWrapper::rotateShip(){
  if (this->_ship->length() > 1) {
    if (this->_ship->orient() == horizontal) {
      this->_ship->setOrient(vertical);
      this->_node->roll(Ogre::Radian(Ogre::Degree(-90)));
    }
    else{
      this->_ship->setOrient(horizontal);
      this->_node->roll(Ogre::Radian(Ogre::Degree(90)));
    }
  }
}

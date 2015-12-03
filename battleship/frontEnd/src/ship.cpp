// Copyright [2015] <Alfredo Arteaga>
#include "ship.h"
Ship::Ship(char* id):_id(id){
}
void Ship::paintShip(Ogre::SceneManager * _sceneManager,
                             Ogre::SceneNode * _parentNode,                             
                              Ogre::Vector3* position) {
  Ogre::SceneNode* node = _sceneManager->createSceneNode(this->_id);
  Ogre::Entity* _ship = _sceneManager->createEntity("ship.mesh");
  node->attachObject(_ship);
  node->translate(*position,Ogre::Node::TS_WORLD);
  _sceneManager->getRootSceneNode()->addChild(node);
}

Ship::~Ship(){
}

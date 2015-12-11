// Copyright [2015] <Alfredo Arteaga>
#include "shipOgreWrapper.h"
#include "const.h"
#include <string>

ShipOgreWrapper::ShipOgreWrapper(int id, Ogre::Vector3* position):_id(id),_originalPosition(position) {
}
void ShipOgreWrapper::paintShip(Ogre::SceneManager * _sceneManager,
                                Ogre::SceneNode * _parentNode,                             
                                Ogre::Vector3* position) {
   std::stringstream ss;
  ss << this->_id;
  Ogre::SceneNode* node = _sceneManager->createSceneNode(ss.str());
  std::cout << "pintando barco " << this->_id <<std::endl;
  Ogre::Entity* _ship = _sceneManager->createEntity("ship.mesh");
  _ship->setQueryFlags(SHIP);
  node->attachObject(_ship);
  std::cout << "kk1";
  
  if (position == NULL) {
    node->translate(*(this->_originalPosition), Ogre::Node::TS_WORLD);                                                               
  }
  else {                                                         
    node->translate(*position,Ogre::Node::TS_WORLD);
  }
  
    std::cout << "kk2";
  _parentNode->addChild(node);
}

                          



ShipOgreWrapper::~ShipOgreWrapper(){
  delete this->_originalPosition;
}

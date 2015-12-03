// Copyright [2015] <Alfredo Arteaga>
#include "board.h"
Board::Board(char* id):_id(id){
}
void Board::paintBoard(Ogre::SceneManager * _sceneManager,
                             Ogre::SceneNode * _parentNode,                             
                              Ogre::Vector3* position) {
  Ogre::SceneNode* node = _sceneManager->createSceneNode(this->_id);
  Ogre::Entity* _board = _sceneManager->createEntity("board.mesh");
  node->attachObject(_board);
  node->translate(*position,Ogre::Node::TS_WORLD);
  _sceneManager->getRootSceneNode()->addChild(node);
}

Board::~Board(){
}

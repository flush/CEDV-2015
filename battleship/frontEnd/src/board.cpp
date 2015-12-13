// Copyright [2015] <Alfredo Arteaga>

#include <sstream>
#include "board.h"
#include "const.h"


Board::Board(char* id):_id(id) {
  this->firstBoxpos = new Ogre::Vector3(-1.8, 1.75, 0);
  this->fleetBoard = new fleet();
}
void Board::paintBoard(Ogre::SceneManager * _sceneManager,
                       Ogre::SceneNode * _parentNode,                             
                       Ogre::Vector3* position) {
  Ogre::SceneNode* nodeBoard = _sceneManager->createSceneNode(this->_id);
  Ogre::Entity* _board = _sceneManager->createEntity("board.mesh");
  _board->setQueryFlags(BOARD_POS);
  nodeBoard->attachObject(_board);

  this->placeBoxes(this->_id, nodeBoard, _sceneManager);
  nodeBoard->translate(*position, Ogre::Node::TS_WORLD);
  _sceneManager->getRootSceneNode()->addChild(nodeBoard);
}

/*
 * place fakeBoxes in the board Gaps to detect positions
 */
void Board::placeBoxes(char* idBoard, Ogre::Node* boardNode,
                       Ogre::SceneManager* _sceneManager) {
  float x_gap = 0.5;
  float y_gap =-0.5;
  for (int i=0; i < 8; i++) {
    for (int j=0; j < 8; j++) {
      ostringstream strConverter;
      strConverter << idBoard << "-" << i << j;
      Ogre::Entity* _box = _sceneManager->createEntity("casilla.mesh");
      _box->setQueryFlags(BOARD_BOX);
      Ogre::SceneNode* nodeBox = _sceneManager->
                                 createSceneNode(strConverter.str());
      nodeBox->attachObject(_box);
      nodeBox->translate(this->firstBoxpos->x + x_gap*i,
                         this->firstBoxpos->y + y_gap*j,
                         this->firstBoxpos->z,
                         Ogre::Node::TS_WORLD);
      boardNode->addChild(nodeBox);
    }
  }
}

Board::~Board() {
  this->ships.clear();
}

/*
 * Get a ship by id
 */
ShipOgreWrapper*  Board::getShip(int id) {
  for (std::vector<ShipOgreWrapper>::iterator it = this->ships.begin() ;
       it != this->ships.end(); ++it) {
    if (it->getId() == id) {
      return &*it;
    }
  }
  return NULL;
}
/*
 * Add a ship to the board, if the position is right
 */

void Board::addShip(ShipOgreWrapper *ogreShip ) {
  ship* currentShip = ogreShip->getShip();
  ship* newShip = this->fleetBoard->new_ship(
      currentShip->x(), currentShip->y(),
      currentShip->orient(), currentShip->length() );
  if (newShip != NULL) {
    ogreShip->setShip(newShip);
  }
  this->ships.push_back(*ogreShip);
}

/*
 * return a ship by a sceneNode Specified
 */
ShipOgreWrapper* Board::getShip(Ogre::Node* node){
  int id = node->getName().at(0) -'0';
  return this->getShip(id);
}

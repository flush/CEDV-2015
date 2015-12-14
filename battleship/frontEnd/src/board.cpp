// Copyright [2015] <Alfredo Arteaga>

#include <sstream>
#include "board.h"
#include "const.h"


Board::Board(char* id, int type):_id(id), _type(type) {
  this->firstBoxpos = new Ogre::Vector3(-1.8, 1.75, 0);
  this->fleetBoard = new fleet();
  if (type == SHOOT_BOARD) {
    this->allocate_random_ships();
  }
}


void Board::allocate_random_ships() {
  ship* res  = 0;
  int cont = 0;

  while (cont < 6 )
  {
    int size = 4;
    if (cont < 2) {
      size = 1;
    } else if (cont < 4) {
      size = 2;
    } else if (cont < 5) {
      size = 3;
    }
    res = this->fleetBoard->new_ship ( random(7),random(7),(orientacion)(random(1)),size);
    if (res != NULL) cont++;
  }

//  p->print();
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
      Ogre::SceneNode* nodeBox = _sceneManager->
                                 createSceneNode(strConverter.str());
      nodeBox->attachObject(_box);
      if (_type == FLEET_BOARD) {
        _box->setQueryFlags(BOARD_BOX);
        _box->setVisible(false);
      } else {
        _box->setQueryFlags(SHOOT_BOX);
        _box->setMaterialName("desconocido");

      }
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
  for (std::vector<ShipOgreWrapper*>::iterator it = this->ships.begin() ;
       it != this->ships.end(); ++it) {
    if ((*it)->getId() == id) {
      return *it;
    }
  }
  return NULL;
}


void Board::setShipBoardPosition(int x, int y, int idShip){
  ShipOgreWrapper* ogreShip = this->getShip(idShip);
  ship* currentShip = ogreShip->getShip();
  ship* newShip = this->fleetBoard->new_ship(
      x,y,
      currentShip->orient(), currentShip->length() );
  if (newShip != NULL) {
    ogreShip->setShip(newShip);
  }

}

/*
 * Check if all Ships has been placed
 *
 */
bool Board::areAllShipsPlaced(){
  for (std::vector<ShipOgreWrapper*>::iterator it = this->ships.begin() ;
       it != this->ships.end(); ++it) {
    if ((*it)->isPlaced() == false) {
      return false;
    }
  }
  return true;
}
/*
 * Add a ship to the board, if the position is right
 */

void Board::addShip(ShipOgreWrapper *ogreShip ) {

  this->ships.push_back(ogreShip);
}

/*
 * return a ship by a sceneNode Specified
 */
ShipOgreWrapper* Board::getShip(Ogre::Node* node){
  int id = node->getName().at(0) -'0';
  return this->getShip(id);
}

disp_result Board::shoot(int x, int y,Ogre::SceneNode* node) {

  Ogre::Entity* mEntity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));

  disp_result res = this->fleetBoard->disparo(x, y);
    mEntity->setQueryFlags(USED_SHOOT_BOX);
   
  
  if (res == agua) {
    std::cout << "Resultado Disparo agua" << std::endl;
    mEntity->setMaterialName("agua");
    mEntity->setVisible(true);
  }  else {

    mEntity->setMaterialName("acierto");
    mEntity->setVisible(true);    
    if( res == tocado){
    std::cout << "Resultado Disparo tocado" << std::endl;      
    }
    else if(res == hundido) {
    std::cout << "Resultado Disparo hundido" << std::endl;      
    }
    else if(res == derrota){
    std::cout << "Resultado Disparo derrota" << std::endl;      
    }
      
  }
  return res;

}


disp_result Board::inteligent_cpu_play() {
  fleet *p = this->fleetBoard;
  disp_result res = agua;
  static disp_result prev_res=agua; 

  static int last_xy [2];
  int x;
  int y;
  int tiro_ok=-1; 
  while (tiro_ok !=0)
  {
    if (prev_res==tocado) 
    {
      if (!p->used(last_xy[0]-1,last_xy[1]) || 
          !p->used(last_xy[0]+1,last_xy[1]) || 
          !p->used(last_xy[0]  ,last_xy[1]-1) || 
          !p->used(last_xy[0]  ,last_xy[1]-1))
      {
        x=random(last_xy[0]+1,last_xy[0]-1);
        y=random(last_xy[1]+1,last_xy[1]-1);
      }
      else 
      {
      x=random(7);
      y=random(7);
      }
    }
    else 
    {
      x=random(7);
      y=random(7);
    }

    if (!p->used(x,y)) tiro_ok = 0;
  }
  ostringstream strConverter;
  strConverter << _id << "-" << x << y;
  
  Ogre::SceneNode* node =  Ogre::Root::getSingleton().
                     getSceneManager("mainSM")->getSceneNode(strConverter.str());

  res =  this->shoot(x,y, node);
  cout << "shoot: " << x<<":"<<y<< " " << print_disp_result (res) << endl;
  prev_res = res;
  last_xy [0]=x;
  last_xy [1]=y;
   
  return res;
}

int Board::getPoints(){
  return this->fleetBoard->score();


}

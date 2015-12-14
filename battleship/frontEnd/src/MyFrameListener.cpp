/*********************************************************************
Frame listener para la aplicación de Battleship.
Curso de videojuegos. Primera minidemo.
*********************************************************************/
#include "MyFrameListener.h"
#include "ship.h"
#include "shipOgreWrapper.h"
#include "const.h"
#include <sstream>
#include <string>

/*
 *
 * Constructor Frame Listener
 */
MyFrameListener::MyFrameListener(Ogre::RenderWindow* win) {

  _idSelectedShip = -1;
  _mode = MODE_STARTED;

  OIS::ParamList param;
  size_t windowHandle;  std::ostringstream wHandleStr;

  _win = win;
  _cam = Ogre::Root::getSingleton().
         getSceneManager("mainSM")->getCamera("MainCamera");
  _btnIzqPulsado = false;

  _rayScnQuery = Ogre::Root::getSingleton().
                 getSceneManager("mainSM")->createRayQuery(Ogre::Ray(), 0);

  _rayScnQueryDD = Ogre::Root::getSingleton().
                 getSceneManager("mainSM")->createRayQuery(Ogre::Ray(), 0);

  win->getCustomAttribute("WINDOW", &windowHandle);

  wHandleStr << windowHandle;
  param.insert(std::make_pair("WINDOW", wHandleStr.str()));

  param.insert(std::make_pair(std::string("x11_mouse_grab"),
                              std::string("false")));
  param.insert(std::make_pair(std::string("x11_mouse_hide"),
                              std::string("false")));
  param.insert(std::make_pair(std::string("x11_keyboard_grab"),
                              std::string("false")));
  param.insert(std::make_pair(std::string("XAutoRepeatOn"),
                              std::string("true")));
  _inputManager = OIS::InputManager::createInputSystem(param);

  _keyboard = static_cast<OIS::Keyboard*>
              (_inputManager->createInputObject(OIS::OISKeyboard, false));
  _mouse = static_cast<OIS::Mouse*> (_inputManager->
                                     createInputObject(OIS::OISMouse, false));


  _mouse->getMouseState().width = win->getWidth();
  _mouse->getMouseState().height = win->getHeight();
}
/*
 *Destructor
 */
MyFrameListener::~MyFrameListener() {
  _inputManager->destroyInputObject(_keyboard);
  _inputManager->destroyInputObject(_mouse);
  OIS::InputManager::destroyInputSystem(_inputManager);
  delete this->playerBoard;
  if (this->shootBoard = NULL) {
    delete this->playerBoard;
  }
}


void MyFrameListener::manageShootMode() {
    if (_mouse->getMouseState().buttonDown(OIS::MB_Left) == true
         && this->_btnIzqPulsado == false) {
      this->_btnIzqPulsado = true;
      if (_turn == PLAYER_TURN) {
        this->shootShip();
      }
    } else if (!_mouse->getMouseState().
               buttonDown(OIS::MB_Left) == true) {
      this->_btnIzqPulsado = false;
    }
    if (_turn == CPU_TURN) {
      sleep(1);
      this->playerBoard->inteligent_cpu_play();
      _turn = PLAYER_TURN;
    }
}
/*
 * Runs on each frame starts
 */
bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt) {
    _mouse->capture();
  int mousex = _mouse->getMouseState().X.abs;
  int mousey = _mouse->getMouseState().Y.abs;

  if (_mode == MODE_STARTED) {
    _mode = MODE_PLACE_SHIP;
    createDummyPlane();
    this->paintPlaceShipMode();
  } else if (_mode == MODE_PLACE_SHIP) {
    if ( _mouse->getMouseState().buttonDown(OIS::MB_Left) == true
         && this->_btnIzqPulsado == false) {
      this->_btnIzqPulsado = true;
      this->selectShip();
    } else if (!_mouse->getMouseState().buttonDown(OIS::MB_Left)) {
      this->_btnIzqPulsado = false;
      if (this->_idSelectedShip >= 0) {
        this->setSelectedShipGameCoords();
        //Check if all ships are placed to start playing
        if (this->playerBoard->areAllShipsPlaced() == true) {
          _turn = PLAYER_TURN;
          _mode = MODE_SHOOT;
          this->paintShootingBoard();
        }
      }
      this->_idSelectedShip = -1;
    }
    /*
     * If there is a ship selected, translate drag and drop
     */
    if (this->_idSelectedShip >= 0) {
        const Ogre::Vector3 &position = this->getMouse3DPoint();
        this->playerBoard->getShip(this->_idSelectedShip)
            ->setShipPosition(position);
    }
    if ( _mouse->getMouseState().buttonDown(OIS::MB_Right) == true
       && this->_btnDchoPulsado == false) {
      this->_btnDchoPulsado = true;
      if (this->_idSelectedShip >= 0) {
         this->playerBoard->getShip(this->_idSelectedShip)
             ->rotateShip();
      }
    }
    if (!_mouse->getMouseState().buttonDown(OIS::MB_Right)) {
      this->_btnDchoPulsado = false;
    }

      


  }
  else if (_mode == MODE_SHOOT){
    manageShootMode();
  }
  _keyboard->capture();
  if (_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
    return false;
  }
  return true;
}


void MyFrameListener::paintShootingBoard(){
  Board* board = new Board("shootBoard", SHOOT_BOARD);
  Ogre::Vector3* shootBoardPosition = new Ogre::Vector3(3, 1.0f, 0);
  Ogre::SceneManager* currentSM = Ogre::Root::getSingleton().
                                  getSceneManager("mainSM");
  board->paintBoard(currentSM,
                      currentSM->getRootSceneNode(),
                      shootBoardPosition);
  this->shootBoard = board;
}


void MyFrameListener::shootShip() {
  _rayScnQuery->setSortByDistance(true);
  _rayScnQuery->setQueryMask(SHOOT_BOX);
  int x = _mouse->getMouseState().X.abs;
  int y = _mouse->getMouseState().Y.abs;
  Ogre::Ray ray = this->setRayQuery(x, y);
  _rayScnQuery->setRay(ray);
  Ogre::RaySceneQueryResult &result = _rayScnQuery->execute();
  Ogre::RaySceneQueryResult::iterator it = result.begin();

  for ( ; it != result.end(); it++) {
    if ( it->movable ) {
      string name = it->movable->getParentNode()->getName();
      int x = name.at(name.length()-2)-'0';
      int y = name.at(name.length()-1)-'0';
      shootBoard->shoot(x, y,(Ogre::SceneNode*) it->movable->getParentNode());
      _turn = CPU_TURN;
    }
  }
}



/*
 *Paint the board and the ships needed to place the ships
 * 
 */
void MyFrameListener::paintPlaceShipMode() {
  Board* boardPS = new Board("MyFleetBoard", FLEET_BOARD);

  Ogre::Vector3* fleetBoardPosition = new Ogre::Vector3(-3, 1.0f, 0);
  Ogre::SceneManager* currentSM = Ogre::Root::getSingleton().
                                  getSceneManager("mainSM");
  boardPS->paintBoard(currentSM,
                      currentSM->getRootSceneNode(),
                      fleetBoardPosition);
   for ( int i = 0; i < 6; i++ ) {
    int size = 4;
    if (i < 2) {
      size = 1;
    } else if (i < 4) {
      size = 2;
    } else if (i < 5) {
      size = 3;
    }
    Ogre::Vector3* shipPos = new Ogre::Vector3(shipPositions[i][0]
                                               , shipPositions[i][1],
                                               shipPositions[i][2]);
    ShipOgreWrapper* ship = new ShipOgreWrapper(i, shipPos, size);
    ship->paintShip(currentSM,
                    currentSM->getRootSceneNode(),
                    NULL);
    boardPS->addShip(ship);
  }
  this->playerBoard = boardPS;
}

const void MyFrameListener::setSelectedShipGameCoords() {
  int x = _mouse->getMouseState().X.abs;
  int y = _mouse->getMouseState().Y.abs;
  Ogre::Ray ray = this->setRayQuery(x, y);
  _rayScnQueryDD->setRay(ray);
  _rayScnQueryDD->setSortByDistance(true);
  _rayScnQueryDD-> setQueryMask(BOARD_BOX);
  Ogre::RaySceneQueryResult &result = _rayScnQueryDD->execute();
  Ogre::RaySceneQueryResult::iterator it = result.begin();
  for ( ; it != result.end(); it++) {
    if ( it->movable ) {
      string name = it->movable->getParentNode()->getName();
      int x = name.at(name.length()-2)-'0';
      int y = name.at(name.length()-1)-'0';
      this->playerBoard->setShipBoardPosition(x, y,
                                              this->_idSelectedShip);
    }
  }
}

/*
 *Build Ray Query for getting 3d mouse position
 */
const Ogre::Vector3 MyFrameListener::getMouse3DPoint() {
  int x = _mouse->getMouseState().X.abs;
  int y = _mouse->getMouseState().Y.abs;
  Ogre::Ray ray = this->setRayQuery(x, y);

  _rayScnQueryDD->setRay(ray);
  _rayScnQueryDD->setSortByDistance(true);
  _rayScnQueryDD-> setQueryMask(PLANE_DRAG_DROP);
  Ogre::RaySceneQueryResult &result = _rayScnQueryDD->execute();
  Ogre::RaySceneQueryResult::iterator it = result.begin();
  return ray.getPoint(it->distance);
}
/*
 *Select a Not placed Ship for placing it in the board
 */
void MyFrameListener::selectShip() {
  _rayScnQuery->setSortByDistance(true);
  _rayScnQuery->setQueryMask(SHIP);
  int x = _mouse->getMouseState().X.abs;
  int y = _mouse->getMouseState().Y.abs;
  Ogre::Ray ray = this->setRayQuery(x, y);
  _rayScnQuery->setRay(ray);
  Ogre::RaySceneQueryResult &result = _rayScnQuery->execute();
  Ogre::RaySceneQueryResult::iterator it = result.begin();

  for ( ; it != result.end(); it++) {
    if ( it->movable ) {
      ShipOgreWrapper* selectedShip = playerBoard->
                                      getShip(it->movable->getParentNode());
      if (selectedShip->isPlaced() == false) {
          int id = it->movable->getParentNode()->getName().at(0) -'0';
          this->_idSelectedShip = id;
      }
    }
  }
}

/*
 * Set a RayQuery to obtain de object pointed by the mouse
 */
Ogre::Ray MyFrameListener::setRayQuery(int posx,
                                        int posy) {
  
  Ogre::Ray rayMouse = _cam->
                       getCameraToViewportRay(posx/float(_win->getWidth()),
                                              posy/float(_win->getHeight()));

 
  return (rayMouse);
}


/*
 * Create a fake Plane for Drag and Drop
 */   
void MyFrameListener::createDummyPlane() {
  Ogre::SceneManager* mSceneMgr = Ogre::Root::getSingleton().
       getSceneManager("mainSM");
  Ogre::Plane *mPlane = new Ogre::Plane(Ogre::Vector3::UNIT_Z, 0.5);

  Ogre::MeshManager::getSingleton().createPlane("DnDPlane",
                                                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                          *mPlane,800, 800, 20, 20, true, 1, 5, 5
                                                , Ogre::Vector3::UNIT_Y);
  Ogre::Entity* plane = mSceneMgr->createEntity("DnDPlane");
  plane->setVisible(false);
  plane->setMaterialName("WoodMat");
  plane->setQueryFlags(PLANE_DRAG_DROP);
  Ogre::Root::getSingleton().
      getSceneManager("mainSM")->getRootSceneNode()->
      attachObject(plane);
}



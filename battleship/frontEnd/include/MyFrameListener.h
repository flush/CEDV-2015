#ifndef MYFRAMELISTENER_H
#define MYFRAMELISTENER_H
#define MODE_SHOOT 4
#define MODE_PLACE_SHIP 3
#define MODE_PLAY 2
#define MODE_STARTED 1
#define CPU_TURN 0
#define PLAYER_TURN 1
#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include "shipOgreWrapper.h"
#include "GuiShip.h"
#include "GuiInputHandler.h"
#include <OIS/OIS.h>
#include "board.h"
#include <vector>
#include <functional>
#include <ctime>

class MyFrameListener : public Ogre::FrameListener {
 private:
  float shipPositions[6][3] = {{3.0f, 3.0f, 0.2f}, {1.0f, 3.0f, 0.2f},
                              {3.0f, 1.0f, 0.2f}, {1.0f, 1.0f, 0.2f},
                              {3.0f, -1.0f, 0.2f}, {1.0f, -1.0f, 0.2f}};
  int _idSelectedShip;
  int _turn;
  int _mouseOrgCoord[2];
  Board* playerBoard;
  Board* shootBoard;
  int _mode;
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  Ogre::RenderWindow*_win;
  Ogre::RaySceneQuery* _rayScnQuery;
  Ogre::RaySceneQuery* _rayScnQueryDD;
  bool _btnIzqPulsado;
  bool _btnDchoPulsado;
  Ogre::Camera* _cam;
  const Ogre::Vector3 getMouse3DPoint();
  void createDummyPlane();
  const void setSelectedShipGameCoords();
  void paintShootingBoard();
  void manageShootMode();
  void shootShip();
  GuiShip *_gui;
  GuiInputHandler* _guiHandler;
  MyGUI::Gui* mGUI;
  MyGUI::OgrePlatform* mPlatform;
  void guiButtonPressed(string userName);
  time_t previousTime;
  string _user;

 public:
  explicit MyFrameListener(Ogre::RenderWindow* win);
  ~MyFrameListener();
  bool frameStarted(const Ogre::FrameEvent& evt);
  void paintPlaceShipMode();
  bool areAllShipsPlaced();
  void selectShip();
  Ogre::Ray setRayQuery(int posx, int posy);
};
#endif //MYFRAMELISTENER_H

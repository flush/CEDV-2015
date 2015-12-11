#ifndef MYFRAMELISTENER_H
#define MYFRAMELISTENER_H
#define MODE_PLACE_SHIP 3
#define MODE_PLAY 2
#define MODE_STARTED 1
#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include "shipOgreWrapper.h"
#include <OIS/OIS.h>
#include "board.h"
#include <vector>

class MyFrameListener : public Ogre::FrameListener {
 private:
  float shipPositions[6][3] = {{3.0f, 3.0f, 0.2f}, {1.0f, 3.0f, 0.2f},
                              {3.0f, 1.0f, 0.2f}, {1.0f, 1.0f, 0.2f},
                              {3.0f, -1.0f, 0.2f}, {1.0f, -1.0f, 0.2f}};
  std::vector<ShipOgreWrapper*> _unSettedShips;
  Ogre::SceneNode* _selectedShip;
  int _mouseOrgCoord[2];
  
  OIS::InputManager* _inputManager;
  int _mode;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  Ogre::RenderWindow*_win;
  Ogre::RaySceneQuery* _rayScnQuery;
  Ogre::RaySceneQuery* _rayScnQueryDD;
  bool _btnIzqPulsado;
  Ogre::Camera* _cam;
  const Ogre::Vector3 getMouse3DPoint();
  void createDummyPlane();
  
 public:
  explicit MyFrameListener(Ogre::RenderWindow* win);
  ~MyFrameListener();
  bool frameStarted(const Ogre::FrameEvent& evt);
  void paintPlaceShipMode();
  void selectShip();
  Ogre::Ray setRayQuery(int posx, int posy, int mask);
};
#endif //MYFRAMELISTENER_H

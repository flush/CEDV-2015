#ifndef MYFRAMELISTENER_H
#define MYFRAMELISTENER_H
#define MODE_PLACE_SHIP 3
#define MODE_PLAY 2
#define MODE_STARTED 1
#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include <OIS/OIS.h>
#include "board.h"

class MyFrameListener : public Ogre::FrameListener {
 private:
  float shipPositions[6][3] = {{3.0f, 3.0f, 0.2f}, {2.0f, 3.0f, 0.2f},
                              {3.0f, 2.0f, 0.2f}, {2.0f, 2.0f, 0.2f},
                              {3.0f, 1.0f, 0.2f}, {2.0f, 1.0f, 0.2f}};
  OIS::InputManager* _inputManager;
  int _mode;
  OIS::Keyboard* _keyboard;
 public:
  explicit MyFrameListener(Ogre::RenderWindow* win);
  ~MyFrameListener();
  bool frameStarted(const Ogre::FrameEvent& evt);
  void paintPlaceShipMode();
};
#endif //MYFRAMELISTENER_H

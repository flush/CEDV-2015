#ifndef _BOARD_H
#define _BOARD_H
#include <Ogre.h>
class Board {
 private:
  char* _id;

 public:
  Board(char* id);
  ~Board();
  void paintBoard(Ogre::SceneManager * _sceneManager,
                             Ogre::SceneNode * _parentNode,                             
                              Ogre::Vector3* position);
                          

};





#endif

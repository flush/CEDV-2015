/*********************************************************************
 * Módulo 2. Curso de Experto en Desarrollo de Videojuegos
 * Autor: Carlos González Morcillo     Carlos.Gonzalez@uclm.es
  *
 * You can redistribute and/or modify this file under the terms of the
 * GNU General Public License ad published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * and later version. See <http://www.gnu.org/licenses/>.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.  
 *********************************************************************/
#include "MyFrameListener.h"
#include "ship.h"
#include <sstream>

MyFrameListener::MyFrameListener(Ogre::RenderWindow* win) {
  _mode = MODE_STARTED;
  OIS::ParamList param;
  size_t windowHandle;  std::ostringstream wHandleStr;

  win->getCustomAttribute("WINDOW", &windowHandle);
  wHandleStr << windowHandle;
  param.insert(std::make_pair("WINDOW", wHandleStr.str()));


  _inputManager = OIS::InputManager::createInputSystem(param);
  _keyboard = static_cast<OIS::Keyboard*>
    (_inputManager->createInputObject(OIS::OISKeyboard, false));
}

MyFrameListener::~MyFrameListener() {
  _inputManager->destroyInputObject(_keyboard);
  OIS::InputManager::destroyInputSystem(_inputManager);
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt) {

  if(_mode == MODE_STARTED){
    _mode= MODE_PLACE_SHIP;
    this->paintPlaceShipMode();
  }
  _keyboard->capture();
  if (_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
    return false;
  }
  return true;
}


void MyFrameListener::paintPlaceShipMode() {
  Board boardPS("fleetBoard");
  

  Ogre::Vector3* fleetBoardPosition = new Ogre::Vector3(-2.0f,1.0f,0);
  Ogre::SceneManager* currentSM = Ogre::Root::getSingleton().getSceneManager("mainSM"); 
  boardPS.paintBoard(currentSM,
                     currentSM->getRootSceneNode(),
                fleetBoardPosition);


      for( int i = 0; i < 6; i++ ) {
        Ogre::Vector3* shipPos = new Ogre::Vector3(shipPositions[i][0]
                                                    , shipPositions[i][1],
                                                    shipPositions[i][2]);
        std::ostringstream oss;
        oss << "ship" << i;
        char idbarco [10];
        sprintf(idbarco,"ship%i",i);
        Ship ship(idbarco);

          ship.paintShip(currentSM,
                     currentSM->getRootSceneNode(),
                shipPos);

      }
  
  
  
}

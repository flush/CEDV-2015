#include "GuiInputHandler.h"
#include "MyGUI.h"
#include  <iostream> 

bool GuiInputHandler::keyPressed( const OIS::KeyEvent &arg )
{

    MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
    //...
    return true;
}
 
bool GuiInputHandler::keyReleased( const OIS::KeyEvent &arg )
{
    MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
    //...
    return true;
}

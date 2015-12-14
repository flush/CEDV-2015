#ifndef _GUI_INPUT_HANDLER_
#define _GUI_INPUT_HANDLER_
#include <OIS/OIS.h>
class GuiInputHandler : public OIS::KeyListener{

 public:
   bool keyPressed(const OIS::KeyEvent&);
   bool keyReleased(const OIS::KeyEvent&);

};

                        
#endif;
                   

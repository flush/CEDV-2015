
#include "GuiShip.h"
#include <pthread.h>

void *disable_gui( void *data )
{
  int i=0;
  GuiShip* app = (GuiShip*)data;
  while (1)
  {
    sleep (5);
    if ((i%2)==0)app->disable();
    else app->enable();
    i++;
  }
}

int main(int argc, char **argv) { 
int  iret1;
pthread_t thread1;

        try
        {
                GuiShip* app = new GuiShip();
                app->prepare();
                if (app->create())
                {
                        iret1 = pthread_create( &thread1, NULL, disable_gui, (void*) app);
                        app->run();
                        app->destroy();
                }
                delete app;
                app = 0;
        }
        catch (MyGUI::Exception& _e)
        {
                std::cerr << "An exception has occured" << " : " << _e.getFullDescription().c_str();
                throw;
        }
        return 0;
}



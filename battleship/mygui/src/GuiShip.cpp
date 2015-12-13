//#include "Precompiled.h"
#include "GuiShip.h"
#include "Base/Main.h"
#include <stdlib.h>

using namespace std;


	GuiShip::GuiShip() 
	{
          max_records=DEFAULT_MAX_RECORDS;
          cb = NULL;
          rec.loadFile("");          
	}

	void GuiShip::setupResources()
	{
		base::BaseManager::setupResources();
		addResourceLocation(getRootMedia());
		addResourceLocation(getRootMedia() + "/BATTLESHIP");
                cout << " ROOT MEDIA " << getRootMedia()<<endl;
	}

        void GuiShip::load_scores()
        {
          int result = 0;
          int cont=0;
          string name;
          int points;
          string tmp_users="";
          string tmp_points="";
          char tmp_char [64];

          result = rec.getNext(name,points,true);
          cont++;
          while (result == 0)
          {
              
            if (result == 0)
            {
              sprintf(tmp_char,"\%s\n",name.c_str());
              tmp_users += string(tmp_char);
              sprintf(tmp_char,"\%d\n",points);
              tmp_points += string(tmp_char);
            }
            if (max_records!=0 && cont >= max_records) break;
            result = rec.getNext(name,points);
            cont++;
          }
          records_users_edt->setCaption(tmp_users);
          records_points_edt->setCaption(tmp_points);
        }

	void GuiShip::createScene()
	{
		base::BaseDemoManager::createScene();
		MyGUI::LayoutManager::getInstance().loadLayout("battleship.layout");
		const MyGUI::VectorWidgetPtr& root = MyGUI::LayoutManager::getInstance().loadLayout("HelpPanel.layout");
		if (root.size() == 1)
		root.at(0)->findWidget("Text")->castType<MyGUI::TextBox>()->setCaption("Battleship, juego de hundir barcos");

                play_btn = MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("play");
                exit_btn = MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("exit");
                level_cmb = MyGUI::Gui::getInstance().findWidget<MyGUI::ComboBox>("level");
                records_users_edt = MyGUI::Gui::getInstance().findWidget<MyGUI::TextBox>("records_users");
                records_points_edt = MyGUI::Gui::getInstance().findWidget<MyGUI::TextBox>("records_points");
                user = MyGUI::Gui::getInstance().findWidget<MyGUI::EditBox>("User");

                play_btn->eventMouseButtonClick = MyGUI::newDelegate(this, &GuiShip::notifyButtonPress); 
                exit_btn->eventMouseButtonClick = MyGUI::newDelegate(this, &GuiShip::notifyButtonPress); 

                load_scores();
	}

	void GuiShip::destroyScene()
	{
	}

	void GuiShip::notifyButtonPress(MyGUI::Widget* _widget)
	{
          string name;
          name = _widget->getName();
          std::cout << "BUTTON PRESS " << name << std::endl;

          if (name=="exit") exit (0);
          else if(name == "play") {
             cout << "PLAY" << endl;          
             if (cb)
             {
               this->disable();
               this->cb(this,user->getCaption());
               this->enable(); 
             }
          } 
          size_t l = level_cmb->getIndexSelected();
          if (l != MyGUI::ITEM_NONE) std::cout << "LEVEL : "  << level_cmb->getIndexSelected() << std::endl;
	}
          

void GuiShip::enable ()
{
  play_btn->setEnabled(true);
  exit_btn->setEnabled(true);
  level_cmb->setEnabled(true);
  records_users_edt->setEnabled(true);
  records_points_edt->setEnabled(true);
  user->setEnabled(true);
}

void GuiShip::disable ()
{
  play_btn->setEnabled(false);
  exit_btn->setEnabled(false);
  level_cmb->setEnabled(false);
  records_users_edt->setEnabled(false);
  records_points_edt->setEnabled(false);
  user->setEnabled(false);
}

void GuiShip::setCallback(void (*cb)(void *,string))
{
  this->cb=cb;
}

string GuiShip::getUser()
{
  return user->getCaption();
}

void GuiShip::add_record(string user, int points)
{
  this->rec.add_record (user,points);
  this->rec.saveFile();
  this->rec.loadFile("");
  this->load_scores();
}


/*
//MYGUI_APP(GuiShip)

int main(int argc, char **argv) { 
//return startApp<GuiShip>(); 
        try
        {
                GuiShip* app = new GuiShip();
                app->prepare();
                if (app->create())
                {
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
*/

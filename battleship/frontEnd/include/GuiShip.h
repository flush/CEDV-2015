#ifndef _GUISHIP_
#define _GUISHIP_

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"
#include "records.h"
#include <functional>

#define DEFAULT_MAX_RECORDS 8

class MyFrameListener;
	class GuiShip
	{
	public:
		GuiShip();

		void createScene();

                void disable ();
                void enable ();
          void setCallback(std::function<void(string)> _cb);
                string getUser();
                void add_record(string user, int points);
          void unloadScene();

	private:
		void notifyButtonPress(MyGUI::Widget* _widget);

                void load_scores();
          
          MyFrameListener* frameListener;
                MyGUI::Button* play_btn;
                MyGUI::Button* exit_btn;
                MyGUI::ComboBox* level_cmb;
                MyGUI::TextBox* records_users_edt;
                MyGUI::TextBox* records_points_edt;
                MyGUI::EditBox* user;
          MyGUI::VectorWidgetPtr layout;
                records rec;
                int max_records;
          std::function<void(string)> cb;


	};



#endif // 

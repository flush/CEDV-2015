#ifndef _GUISHIP_
#define _GUISHIP_

#include "Base/BaseDemoManager.h"
#include "records.h"

	class GuiShip : public base::BaseDemoManager
	{
	public:
		GuiShip();

		virtual void createScene();
		virtual void destroyScene();
                void disable ();
                void enable ();

	private:
		void notifyButtonPress(MyGUI::Widget* _widget);
		virtual void setupResources();
                void load_scores();

	private:
                MyGUI::Button* play_btn;
                MyGUI::Button* exit_btn;
                MyGUI::ComboBox* level_cmb;
                MyGUI::TextBox* records_users_edt;
                MyGUI::TextBox* records_points_edt;
                MyGUI::EditBox* user;
                records rec;
                int max_records=8;

	};



#endif // 

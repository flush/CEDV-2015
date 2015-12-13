#ifndef _GUISHIP_
#define _GUISHIP_

#include "Base/BaseDemoManager.h"
#include "records.h"

#define DEFAULT_MAX_RECORDS 8

	class GuiShip : public base::BaseDemoManager
	{
	public:
		GuiShip();

		virtual void createScene();
		virtual void destroyScene();
                void disable ();
                void enable ();
                void setCallback(void (*cb)(void *,string));
                string getUser();
                void add_record(string user, int points);

	private:
		void notifyButtonPress(MyGUI::Widget* _widget);
		virtual void setupResources();
                void load_scores();

                MyGUI::Button* play_btn;
                MyGUI::Button* exit_btn;
                MyGUI::ComboBox* level_cmb;
                MyGUI::TextBox* records_users_edt;
                MyGUI::TextBox* records_points_edt;
                MyGUI::EditBox* user;
                records rec;
                int max_records;
                void (*cb) (void *,string);

	};



#endif // 

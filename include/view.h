#ifndef UI_CC_VIEW_H_
#define UI_CC_VIEW_H_

#include <iostream>
#include <cstddef>
#include <string>
#include <list>
#include <iterator>



#include "entity.h"
#include "attribute.h"

namespace ui {

class View {
	public:
		View();
		~View();
		void Clear();
		void ShowTitle();
		void ShowMessage(std::string str );
		void ShowStatusBar(std::string name, long int header, long int size );
		void ShowListEntities(std::list<dictionary::Entity> list_entities);
		void ShowMainMenu();
		void ShowFileMenu();
		void ShowDictionaryMenu();
		void ShowEntityMenu();
		void ShowAttributeMenu();

};


}  // end namespace ui

#endif  // UI_CC_VIEW_H_
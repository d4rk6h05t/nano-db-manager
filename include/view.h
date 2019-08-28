#ifndef UI_CC_VIEW_H_
#define UI_CC_VIEW_H_

#include <iostream>
#include <iomanip>    
#include <sstream>
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
		void ShowTitle(const std::string & author,const std::string & version);
		void ShowMessage(const std::string & str );
		void ShowStatusBar(const std::string & name, long int header, long int size );
		void ShowListEntities(std::list<dictionary::Entity> list_entities);
		void ShowListAttributes(std::list<dictionary::Attribute> list_attributes);
		void ShowMainMenu();
		void ShowFileMenu();
		void ShowDictionaryMenu();
		void ShowEntityMenu();
		void ShowAttributeMenu();
		void ShowDataFileMenu();


};


}  // end namespace ui

#endif  // UI_CC_VIEW_H_